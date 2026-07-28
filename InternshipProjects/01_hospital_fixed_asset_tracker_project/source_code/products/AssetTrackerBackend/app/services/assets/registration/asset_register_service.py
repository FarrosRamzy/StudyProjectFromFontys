"""
File: asset_register_service.py
Author: Farros Ramzy (you@domain.com)
Description: Asset registration service.
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
    has_recent_registration_scan,
    validate_initial_checkpoint_node,
)
from app.utils import now_wib


def register_asset_record(
    tag_id: str,
    item_name: str,
    registration_node_id: str,
    initial_room_name: str,
    initial_node_id: str = "",
):
    event_time = now_wib()
    db = SessionLocal()

    try:
        node = get_registration_node(db, registration_node_id)
        if node is None:
            return None

        if not has_recent_registration_scan(db, tag_id, registration_node_id):
            return {
                "message": "registration_failed",
                "reason": "tag_not_recently_scanned_at_registration_node",
            }

        hospital_id = node.hospital_id or ""
        hospital_name = node.hospital_name or ""
        room_name = node.room_name or "REGISTRATION_DESK"

        initial_room_name = initial_room_name.strip()
        initial_node_id = initial_node_id.strip()

        if not initial_room_name:
            return {
                "message": "registration_failed",
                "reason": "initial_room_required",
            }

        validation_error = validate_initial_checkpoint_node(
            db=db,
            initial_node_id=initial_node_id,
            initial_room_name=initial_room_name,
            hospital_id=hospital_id,
        )

        if validation_error:
            return validation_error

        asset = db.query(Asset).filter(Asset.tag_id == tag_id).first()

        if asset is not None and asset.status == "active":
            return {
                "message": "registration_failed",
                "reason": "tag_already_registered",
            }

        if asset is None:
            asset = Asset(tag_id=tag_id)

        asset.item_name = item_name.strip()
        asset.status = "active"
        asset.hospital_id = hospital_id
        asset.hospital_name = hospital_name
        asset.last_room_name = room_name
        asset.last_device_id = registration_node_id
        asset.last_node_id = registration_node_id
        asset.registered_at = asset.registered_at or event_time
        asset.last_seen_at = event_time
        asset.flow_status = "pending_placement"
        asset.expected_room_name = initial_room_name
        asset.expected_node_id = initial_node_id
        asset.assigned_room_name = initial_room_name
        asset.assigned_node_id = initial_node_id
        asset.active_movement_request_id = None
        asset.movement_note = (
            f"Waiting for initial placement at {initial_room_name.strip()}."
        )

        db.add(asset)
        db.commit()
        db.refresh(asset)

    except SQLAlchemyError as exc:
        db.rollback()
        print(f"[DB] Failed to register asset: {exc}")
        return None

    finally:
        db.close()

    create_asset_event(
        tag_id=tag_id,
        device_id=registration_node_id,
        hospital_id=hospital_id,
        hospital_name=hospital_name,
        room_name=room_name,
        event_type="REGISTER",
        timestamp=event_time,
        raw_payload={
            "tag_id": tag_id,
            "item_name": item_name,
            "registration_node_id": registration_node_id,
            "initial_room_name": initial_room_name,
            "initial_node_id": initial_node_id,
        },
    )

    return asset
