"""
File: asset_flow_pending_placement.py
Author: Farros Ramzy (you@domain.com)
Description: Resolves newly registered asset placement flow.
Version: 0.1
Date: 2026-06-12

Copyright (c) 2026
"""


def resolve_pending_placement_flow(db, asset, context: dict) -> None:
    if context["expected_destination_matches"]:
        _mark_initial_placement_completed(asset)
        return

    _mark_initial_placement_mismatch(asset, context)


def _mark_initial_placement_completed(asset) -> None:
    asset.flow_status = "available"
    asset.expected_room_name = ""
    asset.expected_node_id = ""
    asset.active_movement_request_id = None
    asset.movement_note = "Asset reached its initial assigned location."


def _mark_initial_placement_mismatch(asset, context: dict) -> None:
    asset.flow_status = "wrong_location"
    asset.movement_note = (
        f"Initial placement mismatch. "
        f"Expected {context['expected_location_label']}, "
        f"but detected at {context['detected_location_label']}."
    )
