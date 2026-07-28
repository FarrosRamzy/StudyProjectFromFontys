"""
File: test_asset_location_timestamp_service.py
Author: Farros Ramzy (you@domain.com)
Description: Asset location service timestamp tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from datetime import timedelta

from app.services.assets.asset_location_service import update_asset_location
from app.utils import now_wib


def test_update_asset_location_rejects_older_timestamp(make_asset):
    current_time = now_wib()

    make_asset(
        tag_id="TAG_LOC_3",
        status="active",
        last_seen_at=current_time,
    )

    result = update_asset_location(
        tag_id="TAG_LOC_3",
        device_id="NODE_ER",
        room_name="ER",
        hospital_id="HOSP_1",
        hospital_name="General Hospital",
        timestamp=current_time - timedelta(seconds=10),
    )

    assert result["status"] == "stale"

def test_update_asset_location_rejects_same_node_duplicate_within_three_seconds(
    make_asset,
):
    current_time = now_wib()

    make_asset(
        tag_id="TAG_LOC_4",
        status="active",
        last_device_id="NODE_ICU",
        last_node_id="NODE_ICU",
        last_seen_at=current_time,
    )

    result = update_asset_location(
        tag_id="TAG_LOC_4",
        device_id="NODE_ICU",
        room_name="ICU",
        hospital_id="HOSP_1",
        hospital_name="General Hospital",
        timestamp=current_time + timedelta(seconds=1),
    )

    assert result["status"] == "duplicate"

def test_update_asset_location_accepts_newer_timestamp_from_different_node(
    make_asset,
):
    current_time = now_wib()

    make_asset(
        tag_id="TAG_LOC_5",
        status="active",
        last_room_name="ICU",
        last_device_id="NODE_ICU",
        last_node_id="NODE_ICU",
        last_seen_at=current_time,
        flow_status="available",
        assigned_room_name="ER",
        assigned_node_id="NODE_ER",
    )

    result = update_asset_location(
        tag_id="TAG_LOC_5",
        device_id="NODE_ER",
        room_name="ER",
        hospital_id="HOSP_1",
        hospital_name="General Hospital",
        timestamp=current_time + timedelta(seconds=1),
    )

    assert result["status"] == "updated"
    assert result["asset"].last_room_name == "ER"
    assert result["asset"].last_node_id == "NODE_ER"
