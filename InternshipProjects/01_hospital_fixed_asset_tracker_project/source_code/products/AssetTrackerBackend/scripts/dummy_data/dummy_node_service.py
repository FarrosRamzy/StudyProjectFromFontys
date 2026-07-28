"""
File: dummy_node_service.py
Author: Farros Ramzy (you@domain.com)
Description: Database helpers for dummy node scripts.
Version: 0.1
Date: 2026-06-02

Copyright (c) 2026
"""

from app.db_models import Node
from app.services.mqtt.settings.mqtt_settings_service import get_active_mqtt_settings
from app.utils import now_wib


def is_discovered_payload(payload: dict) -> bool:
    return not payload.get("role")


def build_node_fields(payload: dict, status: str) -> dict:
    settings = get_active_mqtt_settings()
    discovered = is_discovered_payload(payload)

    return {
        "alias": payload.get("alias", ""),
        "role": "" if discovered else payload["role"],
        "hospital_id": "" if discovered else settings.hospital_id,
        "hospital_name": "" if discovered else get_hospital_name(settings),
        "room_name": "" if discovered else payload.get("room_name", ""),
        "mqtt_host": "" if discovered else settings.broker_host,
        "mqtt_port": settings.broker_port,
        "is_provisioned": not discovered,
        "status": "DISCOVERED" if discovered else status,
        "last_event_at": now_wib(),
        "last_message": get_last_message(discovered, status),
    }


def get_hospital_name(settings) -> str:
    return settings.hospital_id.replace("-", " ").title()


def get_last_message(discovered: bool, status: str) -> str:
    if discovered:
        return "dummy node awaiting assignment"

    if status == "ONLINE":
        return "dummy node seeded as online"

    return "dummy node seeded for monitor testing"


def upsert_dummy_node(db, payload: dict, status: str) -> Node:
    device_id = payload["device_id"]
    node = db.query(Node).filter(Node.device_id == device_id).first()

    if node is None:
        node = Node(device_id=device_id)

    for key, value in build_node_fields(payload, status).items():
        setattr(node, key, value)

    if status == "ONLINE" and node.is_provisioned:
        node.last_ping_at = now_wib()
    else:
        node.last_ping_at = None

    db.add(node)
    return node


def count_node_asset_references(db, device_id: str) -> int:
    from app.db_models import Asset

    return (
        db.query(Asset)
        .filter(
            (Asset.assigned_node_id == device_id)
            | (Asset.expected_node_id == device_id)
            | (Asset.last_node_id == device_id)
            | (Asset.last_device_id == device_id)
        )
        .count()
    )
