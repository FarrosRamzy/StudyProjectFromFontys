"""
File: mqtt_node_status_handler.py
Author: Farros Ramzy (you@domain.com)
Description: Coordinates MQTT node status handling.
Version: 2.0
Date: 2026-04-30

Copyright (c) 2026
"""

from app.database import SessionLocal
from app.services.mqtt.status.node_status_cases import (
    handle_disabled_node,
    handle_hospital_mismatch,
    handle_unknown_node,
    handle_unprovisioned_node,
)
from app.services.mqtt.status.node_status_dispatcher import (
    handle_provisioned_node_status,
)
from app.services.mqtt.status.node_status_guard import (
    has_hospital_mismatch,
    is_disabled_node,
    is_missing_device_id,
    is_unprovisioned_node,
)
from app.services.mqtt.status.node_status_payload import build_node_status_payload
from app.services.mqtt.status.node_status_repository import find_node_by_device_id
from app.services.mqtt.status.node_status_writer import (
    patch_missing_hospital_metadata,
    update_latest_mqtt_metadata,
)


def handle_node_status(payload: dict, mqtt_broker: str, mqtt_port: int) -> None:
    status_payload = build_node_status_payload(payload)

    if is_missing_device_id(status_payload):
        print("[MQTT] Heartbeat payload missing device_id.")
        return

    db = SessionLocal()

    try:
        node = find_node_by_device_id(db, status_payload["device_id"])

        if node is None:
            handle_unknown_node(db, status_payload, mqtt_broker, mqtt_port)
            return

        if is_disabled_node(node):
            handle_disabled_node(status_payload)
            return

        if has_hospital_mismatch(node, status_payload):
            handle_hospital_mismatch(node, status_payload)
            return

        patch_missing_hospital_metadata(node, status_payload)

        if is_unprovisioned_node(node):
            handle_unprovisioned_node(db, node, status_payload)
            return

        update_latest_mqtt_metadata(
            node=node,
            status_payload=status_payload,
            mqtt_broker=mqtt_broker,
            mqtt_port=mqtt_port,
        )

        handle_provisioned_node_status(db, node, status_payload)

    finally:
        db.close()
