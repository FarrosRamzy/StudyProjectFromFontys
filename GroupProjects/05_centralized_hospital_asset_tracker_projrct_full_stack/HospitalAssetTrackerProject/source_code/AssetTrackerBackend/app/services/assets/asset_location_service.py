"""
File: asset_location_service.py
Author: Farros Ramzy (you@domain.com)
Description: Description
Version: 0.1
Date: 2026-05-12

Copyright (c) 2026
"""

from datetime import datetime

from sqlalchemy.exc import SQLAlchemyError

from app.database import SessionLocal
from app.db_models import Asset
from app.utils import parse_timestamp


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

        # if last_seen_at and timestamp <= last_seen_at:
        if last_seen_at and incoming_timestamp <= last_seen_at:
            return {
                "status": "stale",
                "asset": asset,
            }

        asset.hospital_id = hospital_id or asset.hospital_id or ""
        asset.hospital_name = hospital_name or asset.hospital_name or ""
        asset.last_room_name = room_name or asset.last_room_name or ""
        asset.last_device_id = device_id
        asset.last_node_id = device_id
        asset.last_seen_at = incoming_timestamp
        # asset.last_seen_at = timestamp

        db.add(asset)
        db.commit()
        db.refresh(asset)

        return {
            "status": "updated",
            "asset": asset,
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


def normalize_asset_timestamp(value):
    if value is None:
        return None

    # if isinstance(value, datetime):
    #     return value

    return parse_timestamp(value)
