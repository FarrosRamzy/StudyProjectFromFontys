"""
File: asset_serializer.py
Author: Farros Ramzy (you@domain.com)
Description: Description
Version: 0.1
Date: 2026-04-23

Copyright (c) 2026
"""

from typing import Any
from app.db_models import Asset
from app.utils import to_wib_iso


def asset_to_dict(asset: Asset) -> dict[str, Any]:
    return {
        "hospital_id": getattr(asset, "hospital_id", "") or "",
        "hospital_name": asset.hospital_name or "",
        
        "tag_id": asset.tag_id,
        "item_name": asset.item_name or "",
        "status": asset.status or "",
        "registered_at": to_wib_iso(asset.registered_at),
        
        "last_node_id": asset.last_node_id or "",
        "last_device_id": asset.last_device_id or "",
        "last_room_name": asset.last_room_name or "",
        "last_location": asset.last_room_name or "",
        "last_seen_at": to_wib_iso(asset.last_seen_at),
    }
