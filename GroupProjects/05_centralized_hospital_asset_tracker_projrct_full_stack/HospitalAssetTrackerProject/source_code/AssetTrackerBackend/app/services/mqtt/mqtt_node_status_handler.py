"""
File: mqtt_node_status_handler.py
Author: Farros Ramzy (you@domain.com)
Description: Description
Version: 2.0
Date: 2026-04-30

Copyright (c) 2026
"""

from app.database import SessionLocal
from app.db_models import Node
from app.utils import parse_timestamp, now_wib
from app.serializers.node_serializer import node_to_dict
from app.services.realtime.broadcast_service import schedule_broadcast

VALID_ONLINE_STATUS = {"OK", "ONLINE"}
VALID_OFFLINE_STATUS = {"OFFLINE", "GOODBYE"}


def handle_node_status(payload: dict, mqtt_broker: str, mqtt_port: int) -> None:
    device_id = payload.get("device_id")
    hospital_id = payload.get("hospital_id", "")
    hospital_name = payload.get("hospital_name", "")
    room_name = payload.get("room_name", "")
    message = payload.get("message", "")

    received_at = now_wib()  # Backend receive time.
    timestamp = parse_timestamp(payload.get("timestamp") or received_at)
    status = str(payload.get("status", "")).upper()

    if not device_id:
        print(f"[MQTT] Heartbeat payload missing node_id.")
        return

    db = SessionLocal()
    try:
        node = db.query(Node).filter(Node.device_id == device_id).first()

        # Unknown node: DISCOVERED, but not ONLINE yet.
        if node is None:
            node = Node(
                device_id=device_id,
                alias="",
                role="",
                hospital_id=hospital_id,
                hospital_name=hospital_name,
                room_name=room_name,
                mqtt_host=mqtt_broker,
                mqtt_port=mqtt_port,
                is_provisioned=False,
                status="DISCOVERED",
                last_ping_at=None,
                last_event_at=timestamp,
                last_message="auto-discovered from MQTT status",
            )

            db.add(node)
            db.commit()
            db.refresh(node)

            print(f"[MQTT] Auto-discovered node from heartbeat: {device_id}")

            schedule_broadcast(
                {
                    "type": "node_enrolled",
                    "node": node_to_dict(node),
                }
            )

            return

        # Disabled node: known but intentionally ignored.
        if node.status == "DISABLED":
            print(f"[MQTT] Ignored heartbeat from disabled node: {device_id}")

            schedule_broadcast(
                {
                    "type": "disabled_node_reconnected",
                    "device_id": device_id,
                    "timestamp": received_at.isoformat(),
                }
            )

            return

        # Avoid allowing an MQTT payload to move a provisioned node to another hospital.
        if node.hospital_id and hospital_id and node.hospital_id != hospital_id:
            print(
                f"[MQTT] Ignored heartbeat with hospital mismatch for node {device_id}: "
                f"topic={hospital_id}, db={node.hospital_id}"
            )
            return

        if hospital_id and not node.hospital_id:
            node.hospital_id = hospital_id

        if hospital_name and not node.hospital_name:
            node.hospital_name = hospital_name

        # Unprovisioned node: known but not ASSIGNED yet.
        if not node.is_provisioned:
            node.last_event_at = timestamp
            node.last_message = "heartbeat ignored because node is not provisioned"

            db.add(node)
            db.commit()
            db.refresh(node)

            print(f"[MQTT] Ignored heartbeat from unprovisioned node: {device_id}")
            schedule_broadcast(
                {
                    "type": "node_heartbeat_ignored",
                    "node": node_to_dict(node),
                }
            )
            return

        # Keep latest metadata updated.
        node.mqtt_host = mqtt_broker
        node.mqtt_port = mqtt_port
        node.last_event_at = timestamp

        if node.role == "REGISTRATION":
            node.room_name = ""

        if status in VALID_ONLINE_STATUS:
            node.status = "ONLINE"
            node.last_ping_at = received_at
            node.last_message = message or "heartbeat"

            db.add(node)
            db.commit()
            db.refresh(node)

            print(f"[MQTT] Heartbeat received from node: {device_id}")
            schedule_broadcast(
                {
                    "type": "node_heartbeat",
                    "node": node_to_dict(node),
                }
            )
            return

        if status in VALID_OFFLINE_STATUS:
            node.status = "OFFLINE"
            node.last_ping_at = received_at
            node.last_event_at = timestamp
            node.last_message = message or "node offline"

            db.add(node)
            db.commit()
            db.refresh(node)

            print(f"[MQTT] Node offline: {device_id}")
            schedule_broadcast(
                {
                    "type": "node_offline",
                    "node": node_to_dict(node),
                }
            )
            return

        node.status = node.status or "DISCOVERED"
        node.last_message = message or f"unknown status: {status}"

        db.add(node)
        db.commit()
        db.refresh(node)

        print(f"[MQTT] Unknown node status '{status}' from node: {device_id}")

        schedule_broadcast(
            {
                "type": "node_status_unknown",
                "node": node_to_dict(node),
                "raw_status": status,
            }
        )

    finally:
        db.close()
