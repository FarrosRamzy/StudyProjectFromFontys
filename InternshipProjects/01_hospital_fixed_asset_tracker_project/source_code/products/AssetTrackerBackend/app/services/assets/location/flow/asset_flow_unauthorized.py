"""
File: asset_flow_unauthorized.py
Author: Farros Ramzy (you@domain.com)
Description: Resolves unauthorized movement flow.
Version: 0.1
Date: 2026-06-12

Copyright (c) 2026
"""

from app.services.assets.location.flow.asset_flow_repository import (
    find_active_movement_request,
)


def resolve_unauthorized_movement_flow(db, asset, context: dict) -> None:
    if context["assigned_location_matches"]:
        _handle_return_to_assigned_location(db, asset)
        return

    asset.movement_note = (
        f"Unauthorized movement is still unresolved. "
        f"Asset detected at {context['detected_location_label']}."
    )


def _handle_return_to_assigned_location(db, asset) -> None:
    active_request = find_active_movement_request(
        db=db,
        movement_request_id=asset.active_movement_request_id,
    )

    if active_request and active_request.status == "pending":
        asset.flow_status = "movement_requested"
        asset.movement_note = (
            f"Asset returned to its assigned location. "
            f"Movement request is still waiting for registration desk approval."
        )
        return

    asset.flow_status = "available"
    asset.expected_room_name = ""
    asset.expected_node_id = ""
    asset.active_movement_request_id = None
    asset.movement_note = "Asset returned to its assigned location."
