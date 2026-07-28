"""
File: test_asset_movement_decision_service.py
Author: Farros Ramzy (you@domain.com)
Description: Asset movement service decisions tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from types import SimpleNamespace

from app.services.assets.asset_movement_service import approve_asset_movement_request, cancel_asset_movement_request, create_asset_movement_request, reject_asset_movement_request


def test_approve_asset_movement_request_succeeds(
    db_session,
    make_asset,
    make_node,
    make_movement_request,
):
    make_node(
        device_id="REG_NODE",
        role="REGISTRATION",
        room_name="",
        hospital_id="HOSP_1",
        is_provisioned=True,
        status="ONLINE",
    )

    make_asset(
        tag_id="TAG_MOVE_5",
        status="active",
        flow_status="movement_requested",
        assigned_room_name="ICU",
        assigned_node_id="NODE_ICU",
        expected_room_name="ER",
        expected_node_id="NODE_ER",
    )

    movement = make_movement_request(
        tag_id="TAG_MOVE_5",
        destination_room_name="ER",
        destination_node_id="NODE_ER",
        status="pending",
    )

    req = SimpleNamespace(
        movement_request_id=movement.id,
        registration_node_id="REG_NODE",
    )

    result = approve_asset_movement_request(req, user_id=10)

    assert result["message"] == "movement_approved"
    assert result["asset"]["flow_status"] == "in_transit"
    assert result["movement_request_id"] == movement.id

def test_approve_asset_movement_request_fails_with_checkpoint_registration_node(
    make_node,
    make_asset,
    make_movement_request,
):
    make_node(
        device_id="CHECKPOINT_NODE",
        role="CHECKPOINT",
        room_name="ICU",
        is_provisioned=True,
        status="ONLINE",
    )

    make_asset(tag_id="TAG_MOVE_6", status="active", flow_status="movement_requested")

    movement = make_movement_request(
        tag_id="TAG_MOVE_6",
        status="pending",
    )

    req = SimpleNamespace(
        movement_request_id=movement.id,
        registration_node_id="CHECKPOINT_NODE",
    )

    result = approve_asset_movement_request(req, user_id=10)

    assert result["message"] == "invalid_registration_node"

def test_reject_asset_movement_request_succeeds(
    make_node,
    make_asset,
    make_movement_request,
):
    make_node(
        device_id="REG_NODE",
        role="REGISTRATION",
        room_name="",
        is_provisioned=True,
        status="ONLINE",
    )

    make_asset(
        tag_id="TAG_MOVE_7",
        status="active",
        flow_status="movement_requested",
        assigned_room_name="ICU",
        assigned_node_id="NODE_ICU",
        last_room_name="ICU",
        last_node_id="NODE_ICU",
    )

    movement = make_movement_request(
        tag_id="TAG_MOVE_7",
        status="pending",
    )

    req = SimpleNamespace(
        movement_request_id=movement.id,
        registration_node_id="REG_NODE",
    )

    result = reject_asset_movement_request(req, user_id=10)

    assert result["message"] == "movement_rejected"
    assert result["asset"]["flow_status"] == "available"
