"""
File: dummy_asset_move_modes.py
Author: Farros Ramzy (you@domain.com)
Description: Movement mode helpers for dummy assets.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from app.utils import now_wib


def apply_dummy_move(asset, destination_node, mode: str) -> None:
    if mode == "return":
        apply_return_mode(asset)
        return

    destination_room = destination_node.room_name or ""
    destination_node_id = destination_node.device_id or ""
    apply_last_location(asset, destination_room, destination_node_id)

    if mode == "in-place":
        apply_in_place_mode(asset, destination_room, destination_node_id)
    elif mode == "authorized":
        apply_authorized_mode(asset, destination_room, destination_node_id)
    else:
        apply_unauthorized_mode(asset, destination_room)


def apply_return_mode(asset) -> None:
    asset.last_room_name = asset.assigned_room_name or ""
    asset.last_node_id = asset.assigned_node_id or ""
    asset.last_device_id = asset.assigned_node_id or ""
    asset.last_seen_at = now_wib()
    asset.expected_room_name = ""
    asset.expected_node_id = ""
    asset.active_movement_request_id = None
    asset.flow_status = "available"
    asset.movement_note = "Dummy asset returned to its assigned location."


def apply_last_location(asset, destination_room: str, destination_node_id: str) -> None:
    asset.last_room_name = destination_room
    asset.last_node_id = destination_node_id
    asset.last_device_id = destination_node_id
    asset.last_seen_at = now_wib()


def apply_in_place_mode(asset, destination_room: str, destination_node_id: str) -> None:
    asset.assigned_room_name = destination_room
    asset.assigned_node_id = destination_node_id
    asset.expected_room_name = ""
    asset.expected_node_id = ""
    asset.active_movement_request_id = None
    asset.flow_status = "available"
    asset.movement_note = f"Dummy asset moved and assigned to {destination_room}."


def apply_authorized_mode(asset, destination_room: str, destination_node_id: str) -> None:
    asset.expected_room_name = destination_room
    asset.expected_node_id = destination_node_id
    asset.flow_status = "in_transit"
    asset.movement_note = f"Dummy asset is being moved to {destination_room}."


def apply_unauthorized_mode(asset, destination_room: str) -> None:
    assigned_room = asset.assigned_room_name or asset.assigned_node_id or "-"
    asset.flow_status = "unauthorized_movement"
    asset.movement_note = (
        f"Dummy unauthorized movement. Expected {assigned_room}, "
        f"but detected at {destination_room}."
    )
