"""
File: test_asset_movement_cancel_service.py
Author: Farros Ramzy (you@domain.com)
Description: Asset movement service cancellation tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from types import SimpleNamespace

from app.services.assets.asset_movement_service import approve_asset_movement_request, cancel_asset_movement_request, create_asset_movement_request, reject_asset_movement_request


def test_cancel_asset_movement_request_succeeds_for_request_owner(
    make_asset,
    make_movement_request,
):
    make_asset(
        tag_id="TAG_MOVE_8",
        status="active",
        flow_status="movement_requested",
        assigned_room_name="ICU",
        assigned_node_id="NODE_ICU",
        last_room_name="ICU",
        last_node_id="NODE_ICU",
    )

    movement = make_movement_request(
        tag_id="TAG_MOVE_8",
        status="pending",
        requested_by_user_id=77,
    )

    req = SimpleNamespace(movement_request_id=movement.id)

    result = cancel_asset_movement_request(req, user_id=77)

    assert result["message"] == "movement_cancelled"
    assert result["asset"]["flow_status"] == "available"

def test_cancel_asset_movement_request_fails_for_different_user(
    make_asset,
    make_movement_request,
):
    make_asset(
        tag_id="TAG_MOVE_9",
        status="active",
        flow_status="movement_requested",
    )

    movement = make_movement_request(
        tag_id="TAG_MOVE_9",
        status="pending",
        requested_by_user_id=77,
    )

    req = SimpleNamespace(movement_request_id=movement.id)

    result = cancel_asset_movement_request(req, user_id=88)

    assert result["message"] == "movement_request_not_owned_by_user"
