"""
File: asset_registration_service.py
Author: Farros Ramzy (you@domain.com)
Description: Description
Version: 0.1
Date: 2026-05-12

Copyright (c) 2026
"""

from sqlalchemy.exc import SQLAlchemyError

from app.database import SessionLocal
from app.db_models import Asset, Node
from app.utils import now_wib
from app.services.assets.asset_event_service import create_asset_event


def register_asset_record(tag_id: str, item_name: str, registration_node_id: str):
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
        },
    )

    return asset


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
        asset.last_seen_at = event_time
        asset.last_node_id = registration_node_id
        asset.last_device_id = registration_node_id
        asset.last_room_name = room_name
        asset.hospital_id = hospital_id or asset.hospital_id or ""
        asset.hospital_name = hospital_name or asset.hospital_name or ""

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


def get_registration_node(db, registration_node_id: str):
    node = db.query(Node).filter(Node.device_id == registration_node_id).first()

    if not node:
        return None
    
    if not node.is_provisioned or node.status == "DISABLED":
        return None

    if node.role != "REGISTRATION":
        return None

    return node
