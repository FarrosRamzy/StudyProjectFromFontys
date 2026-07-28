"""
File: test_asset_deregister_service.py
Author: Farros Ramzy (you@domain.com)
Description: Asset deregistration service tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from datetime import timedelta

from app.services.assets.asset_registration_service import deregister_asset_record, register_asset_record
from app.utils import now_wib


def test_deregister_asset_succeeds_from_registration_node(
    make_node,
    make_asset,
):
    make_node(
        device_id="REG_NODE",
        role="REGISTRATION",
        room_name="",
        status="ONLINE",
        is_provisioned=True,
    )

    make_asset(tag_id="TAG_DEREGISTER_1", status="active")

    asset = deregister_asset_record(
        tag_id="TAG_DEREGISTER_1",
        registration_node_id="REG_NODE",
        reason="retired",
    )

    assert asset is not None
    assert asset.status == "deregistered"
    assert asset.deregistered_reason == "retired"
    assert asset.last_node_id == "REG_NODE"

def test_deregister_asset_fails_with_invalid_registration_node(make_asset):
    make_asset(tag_id="TAG_DEREGISTER_2", status="active")

    result = deregister_asset_record(
        tag_id="TAG_DEREGISTER_2",
        registration_node_id="MISSING_REG_NODE",
        reason="invalid node",
    )

    assert result is None
