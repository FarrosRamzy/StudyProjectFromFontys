"""
File: asset_serializer.py
Author: Farros Ramzy (you@domain.com)
Description: Converts asset database records into API and WebSocket response dictionaries.
Version: 0.1
Date: 2026-04-23

Copyright (c) 2026
"""

from typing import Any
from app.db_models import Asset
from app.utils import to_wib_iso


def asset_to_dict(asset: Asset) -> dict[str, Any]:
    return {
        # Hospital Identity
        "hospital_id": getattr(asset, "hospital_id", "") or "",
        "hospital_name": asset.hospital_name or "",
        # Asset Identity & Lifecycle
        "tag_id": asset.tag_id,
        "item_name": asset.item_name or "",
        "status": asset.status or "",
        "registered_at": to_wib_iso(asset.registered_at),
        "deregistered_at": to_wib_iso(getattr(asset, "deregistered_at", None)),
        "deregistered_reason": (getattr(asset, "deregistered_reason", "") or ""),
        # Asset Movement Data
        "last_node_id": asset.last_node_id or "",
        "last_device_id": asset.last_device_id or "",
        "last_room_name": asset.last_room_name or "",
        "last_location": asset.last_room_name or "",
        "last_seen_at": to_wib_iso(asset.last_seen_at),
        # Asset Placement Data
        "flow_status": asset.flow_status or "",
        "expected_room_name": asset.expected_room_name or "",
        "expected_node_id": asset.expected_node_id or "",
        "assigned_room_name": asset.assigned_room_name or "",
        "assigned_node_id": asset.assigned_node_id or "",
        "active_movement_request_id": asset.active_movement_request_id,
        "movement_note": asset.movement_note or "",
    }
