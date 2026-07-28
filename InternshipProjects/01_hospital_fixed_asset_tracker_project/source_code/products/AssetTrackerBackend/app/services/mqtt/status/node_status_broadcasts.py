"""
File: node_status_broadcasts.py
Author: Farros Ramzy (you@domain.com)
Description: Broadcast helpers for MQTT node status events.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from app.serializers.node_serializer import node_to_dict
from app.services.realtime.broadcast_service import schedule_broadcast


def broadcast_node_enrolled(node) -> None:
    schedule_broadcast(
        {
            "type": "node_enrolled",
            "node": node_to_dict(node),
        }
    )


def broadcast_disabled_node_reconnected(device_id: str, received_at) -> None:
    schedule_broadcast(
        {
            "type": "disabled_node_reconnected",
            "device_id": device_id,
            "timestamp": received_at.isoformat(),
        }
    )


def broadcast_heartbeat_ignored(node) -> None:
    schedule_broadcast(
        {
            "type": "node_heartbeat_ignored",
            "node": node_to_dict(node),
        }
    )


def broadcast_node_heartbeat(node) -> None:
    schedule_broadcast(
        {
            "type": "node_heartbeat",
            "node": node_to_dict(node),
        }
    )


def broadcast_node_offline(node) -> None:
    schedule_broadcast(
        {
            "type": "node_offline",
            "node": node_to_dict(node),
        }
    )


def broadcast_node_unknown_status(node, raw_status: str) -> None:
    schedule_broadcast(
        {
            "type": "node_status_unknown",
            "node": node_to_dict(node),
            "raw_status": raw_status,
        }
    )
