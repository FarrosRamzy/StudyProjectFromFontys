"""
File: test_asset_register_location_validation_service.py
Author: Farros Ramzy (you@domain.com)
Description: Asset registration service location tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from datetime import timedelta

from app.services.assets.asset_registration_service import deregister_asset_record, register_asset_record
from app.utils import now_wib


def test_register_asset_fails_when_initial_room_is_empty(
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

    make_registration_scan(tag_id="TAG_REGISTER_7", device_id="REG_NODE")

    result = register_asset_record(
        tag_id="TAG_REGISTER_7",
        item_name="Asset Without Room",
        registration_node_id="REG_NODE",
        initial_room_name="   ",
        initial_node_id="",
    )

    assert result["message"] == "registration_failed"
    assert result["reason"] == "initial_room_required"

def test_register_asset_fails_when_initial_node_belongs_to_another_hospital(
    make_node,
    make_registration_scan,
):
    make_node(
        device_id="REG_NODE",
        role="REGISTRATION",
        room_name="",
        hospital_id="HOSP_1",
        status="ONLINE",
        is_provisioned=True,
    )

    make_node(
        device_id="NODE_OTHER_HOSPITAL",
        role="CHECKPOINT",
        room_name="ICU",
        hospital_id="HOSP_2",
        status="ONLINE",
        is_provisioned=True,
    )

    make_registration_scan(
        tag_id="TAG_REGISTER_8",
        device_id="REG_NODE",
        hospital_id="HOSP_1",
    )

    result = register_asset_record(
        tag_id="TAG_REGISTER_8",
        item_name="Wrong Hospital Asset",
        registration_node_id="REG_NODE",
        initial_room_name="ICU",
        initial_node_id="NODE_OTHER_HOSPITAL",
    )

    assert result["message"] == "registration_failed"
    assert result["reason"] == "initial_node_wrong_hospital"
