"""
File: asset_flow_context.py
Author: Farros Ramzy (you@domain.com)
Description: Builds reusable context for asset flow resolution.
Version: 0.1
Date: 2026-06-12

Copyright (c) 2026
"""

from app.services.assets.location.asset_location_matcher import location_matches


def build_asset_flow_context(asset, detected_room_name: str, detected_node_id: str):
    expected_room_name = asset.expected_room_name or ""
    expected_node_id = asset.expected_node_id or ""
    assigned_room_name = asset.assigned_room_name or ""
    assigned_node_id = asset.assigned_node_id or ""

    return {
        "flow_status": asset.flow_status or "available",
        "detected_room_name": detected_room_name,
        "detected_node_id": detected_node_id,
        "expected_room_name": expected_room_name,
        "expected_node_id": expected_node_id,
        "assigned_room_name": assigned_room_name,
        "assigned_node_id": assigned_node_id,
        "expected_destination_matches": _location_matches(
            expected_room_name,
            expected_node_id,
            detected_room_name,
            detected_node_id,
        ),
        "assigned_location_matches": _location_matches(
            assigned_room_name,
            assigned_node_id,
            detected_room_name,
            detected_node_id,
        ),
        "detected_location_label": detected_room_name or detected_node_id,
        "assigned_location_label": assigned_room_name or assigned_node_id,
        "expected_location_label": expected_room_name or expected_node_id,
    }


def _location_matches(
    expected_room_name: str,
    expected_node_id: str,
    detected_room_name: str,
    detected_node_id: str,
) -> bool:
    return location_matches(
        expected_room_name=expected_room_name,
        expected_node_id=expected_node_id,
        detected_room_name=detected_room_name,
        detected_node_id=detected_node_id,
    )
