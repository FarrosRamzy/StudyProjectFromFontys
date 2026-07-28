"""
File: asset_location_update_service.py
Author: Farros Ramzy (you@domain.com)
Description: Updates an asset's latest detected location and resolves its resulting flow state.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from datetime import datetime

from sqlalchemy.exc import SQLAlchemyError

from app.database import SessionLocal
from app.db.asset_db_model import Asset
from app.services.assets.location.asset_flow_resolver import (
    resolve_asset_flow_after_detection,
)
from app.services.assets.location.asset_timestamp_service import (
    normalize_asset_timestamp,
)


def update_asset_location(
    tag_id: str,
    device_id: str,
    room_name: str,
    hospital_id: str,
    hospital_name: str,
    timestamp: datetime,
):
    db = SessionLocal()

    try:
        asset = db.query(Asset).filter(Asset.tag_id == tag_id).first()

        if not asset:
            return {
                "status": "unknown",
                "asset": None,
            }

        if asset.status != "active":
            return {
                "status": "inactive",
                "asset": asset,
            }

        incoming_timestamp = normalize_asset_timestamp(timestamp)
        last_seen_at = normalize_asset_timestamp(asset.last_seen_at)

        if incoming_timestamp is None:
            return {
                "status": "invalid_timestamp",
                "asset": asset,
            }

        if last_seen_at and incoming_timestamp <= last_seen_at:
            return {
                "status": "stale",
                "asset": asset,
            }

        if (
            asset.last_device_id == device_id
            and last_seen_at
            and (incoming_timestamp - last_seen_at).total_seconds() < 3
        ):
            return {
                "status": "duplicate",
                "asset": asset,
            }

        previous_flow_status = asset.flow_status or ""
        previous_movement_request_id = asset.active_movement_request_id

        asset.hospital_id = hospital_id or asset.hospital_id or ""
        asset.hospital_name = hospital_name or asset.hospital_name or ""
        asset.last_room_name = room_name or asset.last_room_name or ""
        asset.last_device_id = device_id
        asset.last_node_id = device_id
        asset.last_seen_at = incoming_timestamp

        resolve_asset_flow_after_detection(
            db=db,
            asset=asset,
            detected_room_name=room_name or "",
            detected_node_id=device_id,
        )

        movement_completed = bool(
            previous_movement_request_id
            and previous_flow_status in {"in_transit", "wrong_location"}
            and asset.flow_status == "available"
            and not asset.active_movement_request_id
        )

        movement_completed = _did_complete_movement(
            previous_flow_status=previous_flow_status,
            previous_movement_request_id=previous_movement_request_id,
            asset=asset,
        )

        db.add(asset)
        db.commit()
        db.refresh(asset)

        return {
            "status": "updated",
            "asset": asset,
            "previous_flow_status": previous_flow_status,
            "previous_movement_request_id": previous_movement_request_id,
            "movement_completed": movement_completed,
            "completed_movement_request_id": (
                previous_movement_request_id if movement_completed else None
            ),
        }

    except SQLAlchemyError as exc:
        db.rollback()
        print(f"[DB] Failed to update asset location: {exc}")
        return {
            "status": "db_error",
            "asset": None,
        }

    finally:
        db.close()


def _did_complete_movement(
    previous_flow_status: str,
    previous_movement_request_id,
    asset: Asset,
) -> bool:
    return bool(
        previous_movement_request_id
        and previous_flow_status in {"in_transit", "wrong_location"}
        and asset.flow_status == "available"
        and not asset.active_movement_request_id
    )
