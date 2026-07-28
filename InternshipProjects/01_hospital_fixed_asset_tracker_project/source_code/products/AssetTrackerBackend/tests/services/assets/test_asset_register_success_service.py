"""
File: test_asset_register_success_service.py
Author: Farros Ramzy (you@domain.com)
Description: Asset registration service success tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from datetime import timedelta

from app.services.assets.asset_registration_service import deregister_asset_record, register_asset_record
from app.utils import now_wib


def test_register_asset_succeeds_after_recent_registration_scan(
    db_session,
    make_node,
    make_registration_scan,
):
    make_node(
        device_id="REG_NODE",
        role="REGISTRATION",
        room_name="",
        hospital_id="HOSP_1",
        hospital_name="General Hospital",
        status="ONLINE",
        is_provisioned=True,
    )

    make_node(
        device_id="NODE_ICU",
        role="CHECKPOINT",
        room_name="ICU",
        hospital_id="HOSP_1",
        hospital_name="General Hospital",
        status="ONLINE",
        is_provisioned=True,
    )

    make_registration_scan(
        tag_id="TAG_REGISTER_1",
        device_id="REG_NODE",
        hospital_id="HOSP_1",
    )

    asset = register_asset_record(
        tag_id="TAG_REGISTER_1",
        item_name="Infusion Pump",
        registration_node_id="REG_NODE",
        initial_room_name="ICU",
        initial_node_id="NODE_ICU",
    )

    assert asset is not None
    assert not isinstance(asset, dict)
    assert asset.tag_id == "TAG_REGISTER_1"
    assert asset.item_name == "Infusion Pump"
    assert asset.status == "active"
    assert asset.flow_status == "pending_placement"
    assert asset.expected_room_name == "ICU"
    assert asset.expected_node_id == "NODE_ICU"
    assert asset.assigned_room_name == "ICU"
    assert asset.assigned_node_id == "NODE_ICU"
