"""
File: mqtt_detection_handler.py
Author: Farros Ramzy (you@domain.com)
Description: Description
Version: 0.1
Date: 2026-04-23

Copyright (c) 2026
"""

from app.database import SessionLocal
from app.db_models import Node
from app.utils import now_wib, parse_timestamp
from app.serializers.asset_serializer import asset_to_dict
from app.services.assets.asset_service import update_asset_location
from app.services.realtime.broadcast_service import schedule_broadcast
from app.services.assets.asset_event_service import create_asset_event


def handle_detection(payload: dict) -> None:
    device_id = payload.get("device_id")
    tag_id = payload.get("tag_id")
    room_name = payload.get("room_name", "")
    hospital_id = payload.get("hospital_id", "")
    hospital_name = payload.get("hospital_name", "")
    timestamp = parse_timestamp(payload.get("timestamp") or now_wib())

    if not tag_id or not device_id:
        print("[MQTT] Detection payload missing tag_id or node_id")
        return

    db = SessionLocal()
    try:
        node = db.query(Node).filter(Node.device_id == device_id).first()

        if node is None:
            print(f"[MQTT] Detection from an unknown node: {device_id}")
            create_asset_event(
                tag_id=tag_id,
                device_id=device_id,
                hospital_id=hospital_id,
                room_name=room_name,
                hospital_name=hospital_name,
                event_type="UNKNOWN_NODE_DETECTION",
                raw_payload=payload,
                timestamp=timestamp,
            )

            schedule_broadcast(
                {
                    "type": "unknown_node_detection",
                    "device_id": device_id,
                    "tag_id": tag_id,
                    "room_name": room_name,
                    "hospital_name": hospital_name,
                    "timestamp": timestamp.isoformat(),
                }
            )
            return

        if node.status == "DISABLED" or not node.is_provisioned:
            print(
                f"[MQTT] Ignored detection from disabled/unprovisioned node: {device_id}"
            )
            return

        if node.role != "CHECKPOINT":
            print(
                f"MQTT Ignored detection from non-checkpoint node: {device_id} role={node.role}"
            )
            return

        if node.hospital_id and hospital_id and node.hospital_id != hospital_id:
            print(
                f"[MQTT] Hospital ID mismatch for node {device_id}: "
                f"topic={hospital_id}, db={node.hospital_id}"
            )
            return

        # Backend database is the source of truth.
        room_name = node.room_name or room_name
        hospital_name = node.hospital_name or hospital_name
        hospital_id = node.hospital_id or hospital_id

    finally:
        db.close()

    result = update_asset_location(
        tag_id=tag_id,
        device_id=device_id,
        room_name=room_name,
        hospital_id=hospital_id,
        hospital_name=hospital_name,
        timestamp=timestamp,
    )

    result_status = result.get("status")
    asset = result.get("asset")

    if result_status == "unknown":
        create_asset_event(
            tag_id=tag_id,
            device_id=device_id,
            hospital_id=hospital_id,
            room_name=room_name,
            hospital_name=hospital_name,
            event_type="UNKNOWN_TAG",
            raw_payload=payload,
            timestamp=timestamp,
        )

        schedule_broadcast(
            {
                "type": "unknown_tag",
                "tag_id": tag_id,
                "device_id": device_id,
                "room_name": room_name,
                "hospital_name": hospital_name,
                "timestamp": timestamp.isoformat(),
            }
        )

        print(f"[MQTT] Unknown tag detected: {tag_id}")
        return

    if result_status == "inactive":
        asset_data = asset_to_dict(asset)

        create_asset_event(
            tag_id=tag_id,
            device_id=device_id,
            hospital_id=hospital_id,
            room_name=room_name,
            hospital_name=hospital_name,
            event_type="INACTIVE_ASSET_DETECTED",
            raw_payload=payload,
            timestamp=timestamp,
        )

        schedule_broadcast(
            {
                "type": "inactive_asset_detected",
                "asset": asset_data,
                "tag_id": tag_id,
                "device_id": device_id,
                "room_name": room_name,
                "hospital_name": hospital_name,
                "timestamp": timestamp.isoformat(),
            }
        )

        print(f"[MQTT] Inactive asset detected: {tag_id}")
        return

    if result_status == "stale":
        print(
            f"[MQTT] Ignored stale detection: "
            f"{tag_id} at {room_name} from {device_id}, timestamp={timestamp.isoformat()}"
        )
        return
    
    if result_status != "updated":
        print(f"[MQTT] Ignored detection with unknown result status: {result_status}")
        return
    
    create_asset_event(
        tag_id=tag_id,
        device_id=device_id,
        hospital_id=hospital_id,
        room_name=room_name,
        hospital_name=hospital_name,
        event_type="DETECTION",
        raw_payload=payload,
        timestamp=timestamp,
    )
    
    # asset_data = asset_to_dict(result)
    asset_data = asset_to_dict(asset)

    print(f"[MQTT] Detection updated asset: {tag_id}->{room_name} ({device_id})")

    schedule_broadcast(
        {
            "type": "asset_updated",
            "asset": asset_data,
            "timestamp": timestamp.isoformat(),
        }
    )
