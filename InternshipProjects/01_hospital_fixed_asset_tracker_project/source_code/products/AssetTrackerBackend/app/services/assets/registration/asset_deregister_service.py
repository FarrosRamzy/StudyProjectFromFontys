"""
File: asset_deregister_service.py
Author: Farros Ramzy (you@domain.com)
Description: Asset deregistration service.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from sqlalchemy.exc import SQLAlchemyError

from app.database import SessionLocal
from app.db_models import Asset
from app.services.assets.asset_event_service import create_asset_event
from app.services.assets.registration.registration_validation_service import (
    get_registration_node,
)
from app.utils import now_wib


def deregister_asset_record(tag_id: str, registration_node_id: str, reason: str = ""):
    event_time = now_wib()
    db = SessionLocal()

    try:
        node = get_registration_node(db, registration_node_id)
        if node is None:
            return None

        hospital_id = node.hospital_id or ""
        hospital_name = node.hospital_name or ""
        room_name = node.room_name or "REGISTRATION_DESK"

        asset = db.query(Asset).filter(Asset.tag_id == tag_id).first()
        if asset is None:
            return None

        asset.status = "deregistered"
        asset.flow_status = "deregistered"
        asset.active_movement_request_id = None
        asset.expected_room_name = ""
        asset.expected_node_id = ""
        asset.movement_note = "Asset deregistered"
        asset.last_seen_at = event_time
        asset.last_node_id = registration_node_id
        asset.last_device_id = registration_node_id
        asset.last_room_name = room_name
        asset.hospital_id = hospital_id or asset.hospital_id or ""
        asset.hospital_name = hospital_name or asset.hospital_name or ""
        asset.deregistered_at = event_time
        asset.deregistered_reason = reason.strip()

        db.add(asset)
        db.commit()
        db.refresh(asset)

    except SQLAlchemyError as exc:
        db.rollback()
        print(f"[DB] Failed to deregister asset: {exc}")
        return None

    finally:
        db.close()

    create_asset_event(
        tag_id=tag_id,
        device_id=registration_node_id,
        hospital_id=hospital_id,
        hospital_name=hospital_name,
        room_name=room_name,
        event_type="DEREGISTER",
        timestamp=event_time,
        raw_payload={
            "tag_id": tag_id,
            "registration_node_id": registration_node_id,
            "reason": reason,
        },
    )

    return asset
