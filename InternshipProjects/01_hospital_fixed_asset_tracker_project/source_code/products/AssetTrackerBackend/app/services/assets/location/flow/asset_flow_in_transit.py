"""
File: asset_flow_in_transit.py
Author: Farros Ramzy (you@domain.com)
Description: Resolves approved in-transit asset flow.
Version: 0.1
Date: 2026-06-12

Copyright (c) 2026
"""

from app.services.assets.location.asset_movement_completion_service import (
    complete_active_movement_request,
)


def resolve_in_transit_flow(db, asset, context: dict) -> None:
    if context["expected_destination_matches"]:
        _complete_arrival(db, asset, context)
        return

    _mark_still_in_transit(asset, context)


def _complete_arrival(db, asset, context: dict) -> None:
    complete_active_movement_request(db, asset)

    asset.flow_status = "available"
    asset.assigned_room_name = context["expected_room_name"]
    asset.assigned_node_id = context["expected_node_id"]
    asset.expected_room_name = ""
    asset.expected_node_id = ""
    asset.active_movement_request_id = None
    asset.movement_note = "Asset arrived at requested destination."


def _mark_still_in_transit(asset, context: dict) -> None:
    asset.flow_status = "in_transit"
    asset.movement_note = (
        f"Asset was approved for movement to {context['expected_location_label']}, "
        f"but currently at {context['detected_location_label']}."
    )
