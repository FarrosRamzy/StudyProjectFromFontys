"""
File: asset_flow_available.py
Author: Farros Ramzy (you@domain.com)
Description: Resolves normal available asset flow.
Version: 0.1
Date: 2026-06-12

Copyright (c) 2026
"""


def resolve_available_flow(db, asset, context: dict) -> None:
    if not _has_assigned_location(context):
        asset.movement_note = "Asset detected, but no assigned location is configured."
        return

    if context["assigned_location_matches"]:
        asset.movement_note = "Asset is in its assigned location."
        return

    _mark_unauthorized_movement(asset, context)


def _has_assigned_location(context: dict) -> bool:
    return bool(context["assigned_room_name"] or context["assigned_node_id"])


def _mark_unauthorized_movement(asset, context: dict) -> None:
    asset.flow_status = "unauthorized_movement"
    asset.movement_note = (
        f"Unauthorized movement detected. "
        f"Expected {context['assigned_location_label']}, "
        f"but detected at {context['detected_location_label']}."
    )
