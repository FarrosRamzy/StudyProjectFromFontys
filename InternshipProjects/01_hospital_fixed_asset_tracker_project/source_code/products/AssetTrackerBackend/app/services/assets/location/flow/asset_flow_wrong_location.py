"""
File: asset_flow_wrong_location.py
Author: Farros Ramzy (you@domain.com)
Description: Resolves wrong location flow.
Version: 0.1
Date: 2026-06-12

Copyright (c) 2026
"""

from app.services.assets.location.asset_movement_completion_service import (
    complete_active_movement_request,
)


def resolve_wrong_location_flow(db, asset, context: dict) -> None:
    if _asset_reached_approved_destination(asset, context):
        _complete_approved_destination(db, asset, context)
        return

    if context["assigned_location_matches"]:
        _mark_returned_to_assigned_location(asset)
        return

    asset.movement_note = (
        f"Asset is still in the wrong location. "
        f"Detected at {context['detected_location_label']}."
    )


def _asset_reached_approved_destination(asset, context: dict) -> bool:
    return bool(
        context["expected_destination_matches"] and asset.active_movement_request_id
    )


def _complete_approved_destination(db, asset, context: dict) -> None:
    complete_active_movement_request(db, asset)

    asset.flow_status = "available"
    asset.assigned_room_name = context["expected_room_name"]
    asset.assigned_node_id = context["expected_node_id"]
    asset.expected_room_name = ""
    asset.expected_node_id = ""
    asset.active_movement_request_id = None
    asset.movement_note = "Asset reached the approved destination."


def _mark_returned_to_assigned_location(asset) -> None:
    asset.flow_status = "available"
    asset.expected_room_name = ""
    asset.expected_node_id = ""
    asset.active_movement_request_id = None
    asset.movement_note = "Asset returned to its assigned location."
