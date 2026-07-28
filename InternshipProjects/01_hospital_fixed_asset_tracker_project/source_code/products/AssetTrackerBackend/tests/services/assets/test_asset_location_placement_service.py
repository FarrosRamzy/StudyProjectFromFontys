"""
File: test_asset_location_placement_service.py
Author: Farros Ramzy (you@domain.com)
Description: Asset location service placement tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from datetime import timedelta

from app.services.assets.asset_location_service import update_asset_location
from app.utils import now_wib


def test_pending_placement_asset_becomes_available_at_initial_location(make_asset):
    current_time = now_wib()

    make_asset(
        tag_id="TAG_LOC_6",
        status="active",
        last_seen_at=current_time - timedelta(minutes=1),
        flow_status="pending_placement",
        assigned_room_name="ICU",
        assigned_node_id="NODE_ICU",
        expected_room_name="ICU",
        expected_node_id="NODE_ICU",
    )

    result = update_asset_location(
        tag_id="TAG_LOC_6",
        device_id="NODE_ICU",
        room_name="ICU",
        hospital_id="HOSP_1",
        hospital_name="General Hospital",
        timestamp=current_time,
    )

    assert result["status"] == "updated"
    assert result["asset"].flow_status == "available"
    assert result["asset"].expected_room_name == ""
    assert result["asset"].expected_node_id == ""
