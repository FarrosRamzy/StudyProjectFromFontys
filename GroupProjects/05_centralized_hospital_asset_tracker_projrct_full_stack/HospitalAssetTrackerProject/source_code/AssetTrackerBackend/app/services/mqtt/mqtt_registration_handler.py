"""
File: mqtt_registration_handler.py
Author: Farros Ramzy (you@domain.com)
Description: Description
Version: 0.1
Date: 2026-05-04

Copyright (c) 2026
"""

from app.database import SessionLocal
from app.db_models import Node
from app.utils import parse_timestamp, now_wib
from app.services.realtime.broadcast_service import schedule_broadcast
from app.services.assets.asset_event_service import create_asset_event


def handle_registration_scan(payload: dict) -> None:
    device_id = payload.get("device_id")
    tag_id = payload.get("tag_id")
    hospital_id = payload.get("hospital_id", "")
    hospital_name = payload.get("hospital_name", "")
    timestamp = parse_timestamp(payload.get("timestamp") or now_wib)

    if not tag_id or not device_id:
        print("[MQTT] Registration scan missing tag_id or device_id")
        return

    db = SessionLocal()
    try:
        node = db.query(Node).filter(Node.device_id == device_id).first()

        if node is None:
            print(f"[MQTT] Registration scan from unknown node: {device_id}")
            return

        if node.status == "DISABLED" or not node.is_provisioned:
            print(
                f"[MQTT] Ignored registration scan from disabled/unprovisioned node: {device_id}"
            )
            return

        if node.role != "REGISTRATION":
            print(
                f"[MQTT] Ignored registration scan from non-registration node: {device_id}"
            )
            return
        
        if node.hospital_id and hospital_id and node.hospital_id != hospital_id:
            print(
                f"[MQTT] Ignored registration scan with hospital mismatch for node {device_id}: "
                f"topic={hospital_id}, db={node.hospital_id}"
            )
            return

        room_name = node.room_name or "REGISTRATION_DESK"
        hospital_name = hospital_name or node.hospital_name or ""
        hospital_id = hospital_id or node.hospital_id or ""

    finally:
        db.close()

    event = create_asset_event(
        tag_id=tag_id,
        device_id=device_id,
        hospital_id=hospital_id,
        hospital_name=hospital_name,
        room_name=room_name,
        event_type="REGISTRATION_SCAN",
        raw_payload=payload,
        timestamp=timestamp,
    )
    
    if event is None:
        print("[MQTT] Warning: registration scan event was not saved.")

    schedule_broadcast(
        {
            "type": "asset_registration_scan",
            "tag_id": tag_id,
            "device_id": device_id,
            "hospital_id": hospital_id,
            "hospital_name": hospital_name,
            "room_name": room_name,
            "timestamp": timestamp.isoformat(),
        }
    )

    print(f"[MQTT] Registration scan received: {tag_id} from {device_id}")
