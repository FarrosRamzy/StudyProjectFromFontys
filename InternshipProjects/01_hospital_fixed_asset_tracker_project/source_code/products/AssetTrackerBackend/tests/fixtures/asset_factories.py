"""
File: asset_factories.py
Author: Farros Ramzy (you@domain.com)
Description: Asset and asset-event factory fixtures.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

import pytest

from app.db_models import Asset, AssetEvent, AssetMovementRequest
from app.utils import now_wib


@pytest.fixture()
def make_asset(db_session):
    def _make_asset(**overrides):
        defaults = {
            "tag_id": "TAG_1",
            "item_name": "Infusion Pump",
            "status": "active",
            "hospital_id": "HOSP_1",
            "hospital_name": "General Hospital",
            "registered_at": now_wib(),
            "last_room_name": "ICU",
            "last_node_id": "NODE_ICU",
            "last_device_id": "NODE_ICU",
            "last_seen_at": now_wib(),
            "flow_status": "available",
            "assigned_room_name": "ICU",
            "assigned_node_id": "NODE_ICU",
            "expected_room_name": "",
            "expected_node_id": "",
            "active_movement_request_id": None,
            "movement_note": "",
            "deregistered_at": None,
            "deregistered_reason": "",
        }
        defaults.update(overrides)
        asset = Asset(**defaults)

        db_session.add(asset)
        db_session.commit()
        db_session.refresh(asset)

        return asset

    return _make_asset


def _create_asset_event(db_session, event_type, **overrides):
    defaults = {
        "tag_id": "TAG_1",
        "device_id": "NODE_1",
        "hospital_id": "HOSP_1",
        "hospital_name": "General Hospital",
        "room_name": "ICU",
        "event_type": event_type,
        "timestamp": now_wib(),
        "raw_payload": "{}",
    }
    defaults.update(overrides)
    event = AssetEvent(**defaults)

    db_session.add(event)
    db_session.commit()
    db_session.refresh(event)

    return event


@pytest.fixture()
def make_registration_scan(db_session):
    def _make_registration_scan(**overrides):
        return _create_asset_event(
            db_session,
            "REGISTRATION_SCAN",
            device_id=overrides.pop("device_id", "REG_NODE"),
            room_name=overrides.pop("room_name", ""),
            **overrides,
        )

    return _make_registration_scan


@pytest.fixture()
def make_asset_event(db_session):
    def _make_asset_event(**overrides):
        return _create_asset_event(
            db_session,
            overrides.pop("event_type", "DETECTED"),
            **overrides,
        )

    return _make_asset_event


@pytest.fixture()
def make_movement_request(db_session):
    def _make_movement_request(**overrides):
        defaults = {
            "hospital_id": "HOSP_1",
            "hospital_name": "General Hospital",
            "tag_id": "TAG_1",
            "item_name": "Infusion Pump",
            "from_room_name": "ICU",
            "from_node_id": "NODE_ICU",
            "destination_room_name": "ER",
            "destination_node_id": "NODE_ER",
            "status": "pending",
            "requested_by_user_id": 1,
            "approved_by_user_id": None,
            "requested_at": now_wib(),
            "approved_at": None,
            "completed_at": None,
            "rejected_at": None,
            "note": "test movement",
        }
        defaults.update(overrides)
        movement = AssetMovementRequest(**defaults)

        db_session.add(movement)
        db_session.commit()
        db_session.refresh(movement)

        return movement

    return _make_movement_request
