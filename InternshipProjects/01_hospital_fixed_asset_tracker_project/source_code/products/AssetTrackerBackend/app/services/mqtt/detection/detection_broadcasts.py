"""
File: detection_broadcasts.py
Author: Farros Ramzy (you@domain.com)
Description: Broadcast helpers for MQTT detection results.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from app.serializers.asset_serializer import asset_to_dict
from app.services.realtime.broadcast_service import schedule_broadcast


def broadcast_unknown_node_detection(context: dict) -> None:
    schedule_broadcast(
        {
            "type": "unknown_node_detection",
            "device_id": context["device_id"],
            "tag_id": context["tag_id"],
            "room_name": context["room_name"],
            "hospital_name": context["hospital_name"],
            "timestamp": context["timestamp"].isoformat(),
        }
    )


def broadcast_unknown_tag(context: dict) -> None:
    schedule_broadcast(
        {
            "type": "unknown_tag",
            "tag_id": context["tag_id"],
            "device_id": context["device_id"],
            "room_name": context["room_name"],
            "hospital_name": context["hospital_name"],
            "timestamp": context["timestamp"].isoformat(),
        }
    )


def broadcast_inactive_asset_detected(asset, context: dict) -> None:
    schedule_broadcast(
        {
            "type": "inactive_asset_detected",
            "asset": asset_to_dict(asset),
            "tag_id": context["tag_id"],
            "device_id": context["device_id"],
            "room_name": context["room_name"],
            "hospital_name": context["hospital_name"],
            "timestamp": context["timestamp"].isoformat(),
        }
    )


def broadcast_asset_updated(asset, context: dict) -> None:
    schedule_broadcast(
        {
            "type": "asset_updated",
            "asset": asset_to_dict(asset),
            "timestamp": context["timestamp"].isoformat(),
        }
    )


def broadcast_asset_movement_completed(asset, context: dict) -> None:
    schedule_broadcast(
        {
            "type": "asset_movement_completed",
            "asset": asset_to_dict(asset),
            "movement_request": {
                "id": context["completed_movement_request_id"],
                "movement_request_id": context["completed_movement_request_id"],
                "tag_id": context["tag_id"],
                "item_name": asset.item_name or "",
                "status": "completed",
            },
            "tag_id": context["tag_id"],
            "device_id": context["device_id"],
            "room_name": context["room_name"],
            "hospital_name": context["hospital_name"],
            "timestamp": context["timestamp"].isoformat(),
        }
    )
