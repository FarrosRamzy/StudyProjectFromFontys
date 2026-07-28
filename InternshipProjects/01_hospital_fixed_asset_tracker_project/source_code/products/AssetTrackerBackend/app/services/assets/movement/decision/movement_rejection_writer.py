"""
File: movement_rejection_writer.py
Author: Farros Ramzy (you@domain.com)
Description: Applies rejection changes to movement and asset records.
Version: 0.1
Date: 2026-06-12

Copyright (c) 2026
"""

from app.services.assets.location.asset_location_matcher import location_matches
from app.utils import now_wib


def reject_movement(db, movement, asset, user_id: int) -> None:
    movement.status = "rejected"
    movement.approved_by_user_id = user_id
    movement.rejected_at = now_wib()

    _update_asset_after_rejection(asset)


def _update_asset_after_rejection(asset) -> None:
    if _asset_is_at_assigned_location(asset):
        _mark_asset_available_after_rejection(asset)
    else:
        _mark_asset_unauthorized_after_rejection(asset)

    asset.expected_room_name = ""
    asset.expected_node_id = ""
    asset.active_movement_request_id = None


def _asset_is_at_assigned_location(asset) -> bool:
    return location_matches(
        expected_room_name=asset.assigned_room_name,
        expected_node_id=asset.assigned_node_id,
        detected_room_name=asset.last_room_name,
        detected_node_id=asset.last_node_id,
    )


def _mark_asset_available_after_rejection(asset) -> None:
    asset.flow_status = "available"
    asset.movement_note = (
        f"Movement request was rejected. Asset remains at "
        f"{asset.assigned_room_name or asset.last_room_name}."
    )


def _mark_asset_unauthorized_after_rejection(asset) -> None:
    asset.flow_status = "unauthorized_movement"
    asset.movement_note = (
        f"Movement request was rejected, but asset is not at its assigned location. "
        f"Expected {asset.assigned_room_name or asset.assigned_node_id}, "
        f"currently detected at {asset.last_room_name or asset.last_node_id}."
    )
