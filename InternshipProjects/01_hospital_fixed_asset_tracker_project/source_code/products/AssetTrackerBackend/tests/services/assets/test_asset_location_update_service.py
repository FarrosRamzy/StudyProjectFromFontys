"""
File: test_asset_location_update_service.py
Author: Farros Ramzy (you@domain.com)
Description: Asset location service update tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from datetime import timedelta

from app.services.assets.asset_location_service import update_asset_location
from app.utils import now_wib


def test_update_asset_location_succeeds_for_known_active_asset(make_asset):
    old_time = now_wib() - timedelta(minutes=5)

    asset = make_asset(
        tag_id="TAG_LOC_1",
        status="active",
        last_room_name="ICU",
        last_node_id="NODE_ICU",
        last_device_id="NODE_ICU",
        last_seen_at=old_time,
        flow_status="available",
        assigned_room_name="ER",
        assigned_node_id="NODE_ER",
    )

    result = update_asset_location(
        tag_id="TAG_LOC_1",
        device_id="NODE_ER",
        room_name="ER",
        hospital_id="HOSP_1",
        hospital_name="General Hospital",
        timestamp=now_wib(),
    )

    assert result["status"] == "updated"
    assert result["asset"].tag_id == asset.tag_id
    assert result["asset"].last_room_name == "ER"
    assert result["asset"].last_node_id == "NODE_ER"
    assert result["asset"].last_device_id == "NODE_ER"

def test_update_asset_location_returns_unknown_for_unregistered_tag():
    result = update_asset_location(
        tag_id="UNKNOWN_TAG",
        device_id="NODE_ICU",
        room_name="ICU",
        hospital_id="HOSP_1",
        hospital_name="General Hospital",
        timestamp=now_wib(),
    )

    assert result["status"] == "unknown"
    assert result["asset"] is None

def test_update_asset_location_returns_inactive_for_deregistered_asset(make_asset):
    make_asset(
        tag_id="TAG_LOC_2",
        status="deregistered",
        last_seen_at=now_wib() - timedelta(minutes=5),
    )

    result = update_asset_location(
        tag_id="TAG_LOC_2",
        device_id="NODE_ICU",
        room_name="ICU",
        hospital_id="HOSP_1",
        hospital_name="General Hospital",
        timestamp=now_wib(),
    )

    assert result["status"] == "inactive"
