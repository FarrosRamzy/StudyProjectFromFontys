"""
File: test_node_service.py
Author: Farros Ramzy (you@domain.com)
Description: Service tests for node enrollment, provisioning, un-assignment, 
             deletion, and reference protection.
Version: 0.1
Date: 2026-05-29

Copyright (c) 2026
"""

from app.services.nodes.node_service import (
    delete_node_record,
    enroll_node_record,
    get_provision_payload,
    unassign_node_record,
)


def test_enroll_new_node_creates_discovered_node(db_session):
    result = enroll_node_record("NODE_NEW")

    assert result["device_id"] == "NODE_NEW"
    assert result["status"] == "DISCOVERED"
    assert result["is_provisioned"] is False
    assert result["last_message"] == "awaiting assignment"


def test_get_provision_payload_creates_discovered_node_if_missing(db_session):
    result = get_provision_payload("NODE_PROVISION_NEW")

    assert result["is_provisioned"] is False
    assert result["role"] == ""
    assert result["hospital_id"] == ""
    assert result["mqtt_port"] == 1883


def test_unassign_node_succeeds_when_no_assets_reference_it(make_node):
    make_node(
        device_id="NODE_FREE",
        role="CHECKPOINT",
        room_name="ICU",
        is_provisioned=True,
        status="ONLINE",
    )

    result = unassign_node_record("NODE_FREE")

    assert result["device_id"] == "NODE_FREE"
    assert result["status"] == "DISABLED"
    assert result["is_provisioned"] is False
    assert result["role"] == ""


def test_unassign_node_returns_none_when_node_missing():
    result = unassign_node_record("MISSING_NODE")

    assert result is None


def test_unassign_node_is_blocked_when_active_asset_assigned_to_node(
    make_node,
    make_asset,
):
    make_node(
        device_id="NODE_BLOCKED",
        role="CHECKPOINT",
        room_name="ICU",
        is_provisioned=True,
        status="ONLINE",
    )

    make_asset(
        tag_id="TAG_NODE_1",
        status="active",
        assigned_node_id="NODE_BLOCKED",
        expected_node_id="",
        last_node_id="",
    )

    result = unassign_node_record("NODE_BLOCKED")

    assert result["message"] == "node_unassign_blocked"
    assert result["blockers"]["assigned_assets_count"] == 1


def test_unassign_node_is_blocked_when_active_asset_expected_at_node(
    make_node,
    make_asset,
):
    make_node(
        device_id="NODE_BLOCKED",
        role="CHECKPOINT",
        room_name="ICU",
        is_provisioned=True,
        status="ONLINE",
    )

    make_asset(
        tag_id="TAG_NODE_2",
        status="active",
        assigned_node_id="NODE_OTHER",
        expected_node_id="NODE_BLOCKED",
        last_node_id="",
    )

    result = unassign_node_record("NODE_BLOCKED")

    assert result["message"] == "node_unassign_blocked"
    assert result["blockers"]["expected_assets_count"] == 1


def test_delete_node_is_blocked_when_node_is_still_provisioned(make_node):
    make_node(
        device_id="NODE_PROVISIONED",
        role="CHECKPOINT",
        room_name="ICU",
        is_provisioned=True,
        status="ONLINE",
    )

    result = delete_node_record("NODE_PROVISIONED")

    assert result["message"] == "node_must_be_unassigned_first"


def test_delete_node_succeeds_after_node_is_disabled(make_node):
    make_node(
        device_id="NODE_DISABLED",
        role="",
        room_name="",
        is_provisioned=False,
        status="DISABLED",
    )

    result = delete_node_record("NODE_DISABLED")

    assert result["message"] == "node_deleted"
    assert result["device_id"] == "NODE_DISABLED"


def test_delete_node_returns_node_not_found_when_missing():
    result = delete_node_record("MISSING_NODE")

    assert result["message"] == "node_not_found"
