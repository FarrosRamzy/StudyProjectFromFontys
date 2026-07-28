"""
File: node_status_writer.py
Author: Farros Ramzy (you@domain.com)
Description: Applies MQTT node status changes to Node models.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""


def patch_missing_hospital_metadata(node, status_payload: dict) -> None:
    if status_payload["hospital_id"] and not node.hospital_id:
        node.hospital_id = status_payload["hospital_id"]

    if status_payload["hospital_name"] and not node.hospital_name:
        node.hospital_name = status_payload["hospital_name"]


def mark_unprovisioned_heartbeat_ignored(node, status_payload: dict) -> None:
    node.last_event_at = status_payload["timestamp"]
    node.last_message = "heartbeat ignored because node is not provisioned"


def update_latest_mqtt_metadata(
    node,
    status_payload: dict,
    mqtt_broker: str,
    mqtt_port: int,
) -> None:
    node.mqtt_host = mqtt_broker
    node.mqtt_port = mqtt_port
    node.last_event_at = status_payload["timestamp"]

    if node.role == "REGISTRATION":
        node.room_name = ""


def mark_node_online(node, status_payload: dict) -> None:
    node.status = "ONLINE"
    node.last_ping_at = status_payload["received_at"]
    node.last_message = status_payload["message"] or "heartbeat"


def mark_node_offline(node, status_payload: dict) -> None:
    node.status = "OFFLINE"
    node.last_ping_at = status_payload["received_at"]
    node.last_event_at = status_payload["timestamp"]
    node.last_message = status_payload["message"] or "node offline"


def mark_node_unknown_status(node, status_payload: dict) -> None:
    node.status = node.status or "DISCOVERED"
    node.last_message = (
        status_payload["message"] or f"unknown status: {status_payload['status']}"
    )
