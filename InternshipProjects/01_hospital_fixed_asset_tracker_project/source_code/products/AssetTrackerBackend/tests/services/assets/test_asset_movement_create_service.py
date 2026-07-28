"""
File: test_asset_movement_create_service.py
Author: Farros Ramzy (you@domain.com)
Description: Asset movement service creation tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from types import SimpleNamespace

from app.services.assets.asset_movement_service import approve_asset_movement_request, cancel_asset_movement_request, create_asset_movement_request, reject_asset_movement_request


def test_create_asset_movement_request_succeeds_for_available_asset(
    db_session,
    make_asset,
    make_node,
):
    make_asset(
        tag_id="TAG_MOVE_1",
        status="active",
        flow_status="available",
        assigned_room_name="ICU",
        assigned_node_id="NODE_ICU",
        last_room_name="ICU",
        last_node_id="NODE_ICU",
    )

    make_node(
        device_id="NODE_ER",
        role="CHECKPOINT",
        room_name="ER",
        hospital_id="HOSP_1",
        is_provisioned=True,
        status="ONLINE",
    )

    req = SimpleNamespace(
        tag_id="TAG_MOVE_1",
        destination_room_name="ER",
        destination_node_id="NODE_ER",
        note="Move to ER",
    )

    result = create_asset_movement_request(req, user_id=1)

    assert result["message"] == "movement_requested"
    assert result["asset"]["flow_status"] == "movement_requested"
    assert result["asset"]["expected_room_name"] == "ER"
    assert result["asset"]["expected_node_id"] == "NODE_ER"
    assert result["movement_request_id"] is not None

def test_create_asset_movement_request_fails_when_asset_missing():
    req = SimpleNamespace(
        tag_id="MISSING_TAG",
        destination_room_name="ER",
        destination_node_id="NODE_ER",
        note="Move to ER",
    )

    result = create_asset_movement_request(req, user_id=1)

    assert result["message"] == "asset_not_found"

def test_create_asset_movement_request_fails_when_asset_not_active(make_asset):
    make_asset(
        tag_id="TAG_MOVE_2",
        status="deregistered",
        flow_status="available",
    )

    req = SimpleNamespace(
        tag_id="TAG_MOVE_2",
        destination_room_name="ER",
        destination_node_id="",
        note="Move to ER",
    )

    result = create_asset_movement_request(req, user_id=1)

    assert result["message"] == "asset_not_active"

def test_create_asset_movement_request_fails_when_asset_not_available(make_asset):
    make_asset(
        tag_id="TAG_MOVE_3",
        status="active",
        flow_status="in_transit",
    )

    req = SimpleNamespace(
        tag_id="TAG_MOVE_3",
        destination_room_name="ER",
        destination_node_id="",
        note="Move to ER",
    )

    result = create_asset_movement_request(req, user_id=1)

    assert result["message"] == "asset_not_available_for_movement"

def test_create_asset_movement_request_fails_when_destination_node_is_wrong_hospital(
    make_asset,
    make_node,
):
    make_asset(
        tag_id="TAG_MOVE_4",
        status="active",
        hospital_id="HOSP_1",
        flow_status="available",
        assigned_room_name="ICU",
        last_room_name="ICU",
    )

    make_node(
        device_id="NODE_OTHER_HOSPITAL",
        role="CHECKPOINT",
        room_name="ER",
        hospital_id="HOSP_2",
        is_provisioned=True,
        status="ONLINE",
    )

    req = SimpleNamespace(
        tag_id="TAG_MOVE_4",
        destination_room_name="ER",
        destination_node_id="NODE_OTHER_HOSPITAL",
        note="Move to ER",
    )

    result = create_asset_movement_request(req, user_id=1)

    assert result["message"] == "destination_node_wrong_hospital"
