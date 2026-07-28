"""
File: test_asset_flow_movement_states.py
Author: Farros Ramzy (you@domain.com)
Description: Asset movement flow resolver tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

try:
    from app.services.assets.location.asset_flow_resolver import resolve_asset_flow_after_detection
except ModuleNotFoundError:
    from app.services.assets.asset_location_service import resolve_asset_flow_after_detection


def test_available_asset_becomes_unauthorized_when_detected_outside_assigned_location(
    db_session,
    make_asset,
):
    asset = make_asset(
        tag_id="TAG_FLOW_3",
        flow_status="available",
        assigned_room_name="ICU",
        assigned_node_id="NODE_ICU",
    )

    resolve_asset_flow_after_detection(
        db=db_session,
        asset=asset,
        detected_room_name="ER",
        detected_node_id="NODE_ER",
    )

    assert asset.flow_status == "unauthorized_movement"
    assert "Unauthorized movement" in asset.movement_note

def test_movement_requested_becomes_unauthorized_if_asset_moves_before_approval(
    db_session,
    make_asset,
):
    asset = make_asset(
        tag_id="TAG_FLOW_4",
        flow_status="movement_requested",
        assigned_room_name="ICU",
        assigned_node_id="NODE_ICU",
        expected_room_name="ER",
        expected_node_id="NODE_ER",
    )

    resolve_asset_flow_after_detection(
        db=db_session,
        asset=asset,
        detected_room_name="ER",
        detected_node_id="NODE_ER",
    )

    assert asset.flow_status == "unauthorized_movement"
    assert "before approval" in asset.movement_note

def test_in_transit_asset_becomes_available_when_reaching_destination(
    db_session,
    make_asset,
    make_movement_request,
):
    movement = make_movement_request(
        tag_id="TAG_FLOW_5",
        destination_room_name="ER",
        destination_node_id="NODE_ER",
        status="approved",
    )

    asset = make_asset(
        tag_id="TAG_FLOW_5",
        flow_status="in_transit",
        assigned_room_name="ICU",
        assigned_node_id="NODE_ICU",
        expected_room_name="ER",
        expected_node_id="NODE_ER",
        active_movement_request_id=movement.id,
    )

    resolve_asset_flow_after_detection(
        db=db_session,
        asset=asset,
        detected_room_name="ER",
        detected_node_id="NODE_ER",
    )

    db_session.commit()
    db_session.refresh(movement)

    assert asset.flow_status == "available"
    assert asset.assigned_room_name == "ER"
    assert asset.assigned_node_id == "NODE_ER"
    assert asset.expected_room_name == ""
    assert asset.expected_node_id == ""
    assert asset.active_movement_request_id is None
    assert movement.status == "completed"
