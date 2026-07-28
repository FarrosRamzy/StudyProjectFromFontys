"""
File: node_status_cases.py
Author: Farros Ramzy (you@domain.com)
Description: Handles individual MQTT node status cases.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from app.services.mqtt.status.node_status_broadcasts import (
    broadcast_disabled_node_reconnected,
    broadcast_heartbeat_ignored,
    broadcast_node_enrolled,
    broadcast_node_heartbeat,
    broadcast_node_offline,
    broadcast_node_unknown_status,
)
from app.services.mqtt.status.node_status_discovery import build_discovered_node
from app.services.mqtt.status.node_status_repository import save_node_status
from app.services.mqtt.status.node_status_writer import (
    mark_node_offline,
    mark_node_online,
    mark_node_unknown_status,
    mark_unprovisioned_heartbeat_ignored,
)


def handle_unknown_node(db, status_payload: dict, mqtt_broker: str, mqtt_port: int):
    node = build_discovered_node(status_payload, mqtt_broker, mqtt_port)
    saved_node = save_node_status(db, node)

    print(f"[MQTT] Auto-discovered node from heartbeat: {status_payload['device_id']}")
    broadcast_node_enrolled(saved_node)


def handle_disabled_node(status_payload: dict) -> None:
    print(f"[MQTT] Ignored heartbeat from disabled node: {status_payload['device_id']}")

    broadcast_disabled_node_reconnected(
        device_id=status_payload["device_id"],
        received_at=status_payload["received_at"],
    )


def handle_hospital_mismatch(node, status_payload: dict) -> None:
    print(
        f"[MQTT] Ignored heartbeat with hospital mismatch for node "
        f"{status_payload['device_id']}: "
        f"topic={status_payload['hospital_id']}, db={node.hospital_id}"
    )


def handle_unprovisioned_node(db, node, status_payload: dict) -> None:
    mark_unprovisioned_heartbeat_ignored(node, status_payload)
    saved_node = save_node_status(db, node)

    print(
        f"[MQTT] Ignored heartbeat from unprovisioned node: {status_payload['device_id']}"
    )
    broadcast_heartbeat_ignored(saved_node)


def handle_online_node(db, node, status_payload: dict) -> None:
    mark_node_online(node, status_payload)
    saved_node = save_node_status(db, node)

    print(f"[MQTT] Heartbeat received from node: {status_payload['device_id']}")
    broadcast_node_heartbeat(saved_node)


def handle_offline_node(db, node, status_payload: dict) -> None:
    mark_node_offline(node, status_payload)
    saved_node = save_node_status(db, node)

    print(f"[MQTT] Node offline: {status_payload['device_id']}")
    broadcast_node_offline(saved_node)


def handle_unknown_status_node(db, node, status_payload: dict) -> None:
    mark_node_unknown_status(node, status_payload)
    saved_node = save_node_status(db, node)

    print(
        f"[MQTT] Unknown node status '{status_payload['status']}' "
        f"from node: {status_payload['device_id']}"
    )

    broadcast_node_unknown_status(
        node=saved_node,
        raw_status=status_payload["status"],
    )
