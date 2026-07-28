"""
File: asset_location_matcher.py
Author: Farros Ramzy (you@domain.com)
Description: Compares detected node and room data against an asset's expected location.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""


def location_matches(
    expected_room_name: str,
    expected_node_id: str,
    detected_room_name: str,
    detected_node_id: str,
) -> bool:
    expected_room_name = (expected_room_name or "").strip()
    expected_node_id = (expected_node_id or "").strip()
    detected_room_name = (detected_room_name or "").strip()
    detected_node_id = (detected_node_id or "").strip()

    room_is_configured = bool(expected_room_name)
    node_is_configured = bool(expected_node_id)

    room_matches = (
        room_is_configured
        and detected_room_name
        and detected_room_name == expected_room_name
    )

    node_matches = (
        node_is_configured and detected_node_id and detected_node_id == expected_node_id
    )

    # If both room and node are configured, both must match.
    if room_is_configured and node_is_configured:
        return bool(room_matches and node_matches)

    # If only node is configured, node match is enough.
    if node_is_configured:
        return bool(node_matches)

    # If only room is configured, room match is enough.
    if room_is_configured:
        return bool(room_matches)

    return False
