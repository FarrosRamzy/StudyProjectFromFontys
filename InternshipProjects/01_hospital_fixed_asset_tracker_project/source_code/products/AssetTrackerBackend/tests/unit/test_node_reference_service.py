"""
File: test_node_reference_service.py
Author: Farros Ramzy (you@domain.com)
Description: Unit tests for detecting asset and movement references that block node removal.
Version: 0.1
Date: 2026-05-29

Copyright (c) 2026
"""

try:
    from app.services.nodes.node_reference_service import find_node_reference_blockers
except ModuleNotFoundError:
    from app.services.nodes.node_service import find_node_reference_blockers


def test_node_has_no_reference_blockers_by_default(db_session):
    blockers = find_node_reference_blockers(db_session, "NODE_EMPTY")

    assert blockers["assigned_assets_count"] == 0
    assert blockers["expected_assets_count"] == 0
    assert blockers["current_location_assets_count"] == 0
    assert blockers["active_movement_requests_count"] == 0
    assert blockers["total"] == 0


def test_node_reference_blockers_count_assigned_asset(db_session, make_asset):
    make_asset(
        tag_id="TAG_BLOCK_1",
        assigned_node_id="NODE_BLOCKED",
        expected_node_id="",
        last_node_id="",
    )

    blockers = find_node_reference_blockers(db_session, "NODE_BLOCKED")

    assert blockers["assigned_assets_count"] == 1
    assert blockers["total"] == 1


def test_node_reference_blockers_count_expected_asset(db_session, make_asset):
    make_asset(
        tag_id="TAG_BLOCK_2",
        assigned_node_id="NODE_OTHER",
        expected_node_id="NODE_BLOCKED",
        last_node_id="",
    )

    blockers = find_node_reference_blockers(db_session, "NODE_BLOCKED")

    assert blockers["expected_assets_count"] == 1
    assert blockers["total"] == 1


def test_node_reference_blockers_count_current_location_asset(db_session, make_asset):
    make_asset(
        tag_id="TAG_BLOCK_3",
        assigned_node_id="NODE_OTHER",
        expected_node_id="",
        last_node_id="NODE_BLOCKED",
    )

    blockers = find_node_reference_blockers(db_session, "NODE_BLOCKED")

    assert blockers["current_location_assets_count"] == 1
    assert blockers["total"] == 1


def test_node_reference_blockers_count_active_movement_request(
    db_session,
    make_movement_request,
):
    make_movement_request(
        tag_id="TAG_BLOCK_4",
        destination_node_id="NODE_BLOCKED",
        status="pending",
    )

    blockers = find_node_reference_blockers(db_session, "NODE_BLOCKED")

    assert blockers["active_movement_requests_count"] == 1
    assert blockers["total"] == 1


def test_node_reference_blockers_ignore_completed_movement_request(
    db_session,
    make_movement_request,
):
    make_movement_request(
        tag_id="TAG_BLOCK_5",
        destination_node_id="NODE_BLOCKED",
        status="completed",
    )

    blockers = find_node_reference_blockers(db_session, "NODE_BLOCKED")

    assert blockers["active_movement_requests_count"] == 0
    assert blockers["total"] == 0
