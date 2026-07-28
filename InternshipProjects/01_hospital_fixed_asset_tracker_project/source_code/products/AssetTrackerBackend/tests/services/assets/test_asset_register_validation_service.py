"""
File: test_asset_register_validation_service.py
Author: Farros Ramzy (you@domain.com)
Description: Asset registration validation service tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from datetime import timedelta

from app.services.assets.asset_registration_service import deregister_asset_record, register_asset_record
from app.utils import now_wib


def test_register_asset_fails_when_registration_node_does_not_exist():
    result = register_asset_record(
        tag_id="TAG_REGISTER_2",
        item_name="Wheelchair",
        registration_node_id="MISSING_REG_NODE",
        initial_room_name="ICU",
        initial_node_id="",
    )

    assert result is None

def test_register_asset_fails_when_node_is_checkpoint(
    make_node,
    make_registration_scan,
):
    make_node(
        device_id="CHECKPOINT_NODE",
        role="CHECKPOINT",
        room_name="ICU",
        status="ONLINE",
        is_provisioned=True,
    )

    make_registration_scan(
        tag_id="TAG_REGISTER_3",
        device_id="CHECKPOINT_NODE",
    )

    result = register_asset_record(
        tag_id="TAG_REGISTER_3",
        item_name="Monitor",
        registration_node_id="CHECKPOINT_NODE",
        initial_room_name="ICU",
        initial_node_id="CHECKPOINT_NODE",
    )

    assert result is None

def test_register_asset_fails_without_recent_registration_scan(make_node):
    make_node(
        device_id="REG_NODE",
        role="REGISTRATION",
        room_name="",
        status="ONLINE",
        is_provisioned=True,
    )

    result = register_asset_record(
        tag_id="TAG_REGISTER_4",
        item_name="Bed",
        registration_node_id="REG_NODE",
        initial_room_name="ICU",
        initial_node_id="",
    )

    assert result["message"] == "registration_failed"
    assert result["reason"] == "tag_not_recently_scanned_at_registration_node"

def test_register_asset_fails_with_old_registration_scan(
    make_node,
    make_registration_scan,
):
    make_node(
        device_id="REG_NODE",
        role="REGISTRATION",
        room_name="",
        status="ONLINE",
        is_provisioned=True,
    )

    make_registration_scan(
        tag_id="TAG_REGISTER_5",
        device_id="REG_NODE",
        timestamp=now_wib() - timedelta(minutes=10),
    )

    result = register_asset_record(
        tag_id="TAG_REGISTER_5",
        item_name="Old Scan Asset",
        registration_node_id="REG_NODE",
        initial_room_name="ICU",
        initial_node_id="",
    )

    assert result["message"] == "registration_failed"
    assert result["reason"] == "tag_not_recently_scanned_at_registration_node"

def test_register_asset_fails_when_tag_already_active(
    make_node,
    make_asset,
    make_registration_scan,
):
    make_node(
        device_id="REG_NODE",
        role="REGISTRATION",
        room_name="",
        status="ONLINE",
        is_provisioned=True,
    )

    make_asset(tag_id="TAG_REGISTER_6", status="active")
    make_registration_scan(tag_id="TAG_REGISTER_6", device_id="REG_NODE")

    result = register_asset_record(
        tag_id="TAG_REGISTER_6",
        item_name="Duplicate Asset",
        registration_node_id="REG_NODE",
        initial_room_name="ICU",
        initial_node_id="",
    )

    assert result["message"] == "registration_failed"
    assert result["reason"] == "tag_already_registered"
