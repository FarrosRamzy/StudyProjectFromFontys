"""
File: test_asset_flow_initial_placement.py
Author: Farros Ramzy (you@domain.com)
Description: Asset flow first placement tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

try:
    from app.services.assets.location.asset_flow_resolver import (
        resolve_asset_flow_after_detection,
    )
except ModuleNotFoundError:
    from app.services.assets.asset_location_service import (
        resolve_asset_flow_after_detection,
    )


def test_pending_placement_becomes_available_when_asset_reaches_expected_location(
    db_session,
    make_asset,
):
    asset = make_asset(
        tag_id="TAG_FLOW_1",
        flow_status="pending_placement",
        assigned_room_name="ICU",
        assigned_node_id="NODE_ICU",
        expected_room_name="ICU",
        expected_node_id="NODE_ICU",
    )

    resolve_asset_flow_after_detection(
        db=db_session,
        asset=asset,
        detected_room_name="ICU",
        detected_node_id="NODE_ICU",
    )

    assert asset.flow_status == "available"
    assert asset.expected_room_name == ""
    assert asset.expected_node_id == ""
    assert asset.active_movement_request_id is None
    assert "initial assigned location" in asset.movement_note


def test_pending_placement_becomes_wrong_location_when_detected_elsewhere(
    db_session,
    make_asset,
):
    asset = make_asset(
        tag_id="TAG_FLOW_2",
        flow_status="pending_placement",
        assigned_room_name="ICU",
        assigned_node_id="NODE_ICU",
        expected_room_name="ICU",
        expected_node_id="NODE_ICU",
    )

    resolve_asset_flow_after_detection(
        db=db_session,
        asset=asset,
        detected_room_name="ER",
        detected_node_id="NODE_ER",
    )

    assert asset.flow_status == "wrong_location"
    assert "Initial placement mismatch" in asset.movement_note
