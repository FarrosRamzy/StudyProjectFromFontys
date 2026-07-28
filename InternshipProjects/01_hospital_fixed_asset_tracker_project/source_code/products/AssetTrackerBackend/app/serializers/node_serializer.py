"""
File: node_serializer.py
Author: Farros Ramzy (you@domain.com)
Description: Converts node database records into API and WebSocket response dictionaries.
Version: 1.5
Date: 2026-04-30

Copyright (c) 2026
"""

from typing import Any
from app.db_models import Node
from app.utils import to_wib_iso


def node_to_dict(node: Node) -> dict[str, Any]:
    return {
        "device_id": node.device_id,
        "alias": node.alias or "",
        "role": node.role or "",
        "hospital_id": getattr(node, "hospital_id", "") or "",
        "hospital_name": node.hospital_name or "",
        "room_name": node.room_name or "",
        "mqtt_host": node.mqtt_host or "",
        "mqtt_port": node.mqtt_port or 1883,
        "is_provisioned": bool(node.is_provisioned),
        "status": node.status or "",
        "last_ping_at": to_wib_iso(node.last_ping_at),
        "last_event_at": to_wib_iso(node.last_event_at),
        "last_message": node.last_message or "",
    }
