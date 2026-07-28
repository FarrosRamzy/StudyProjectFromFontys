"""
File: asset_route_patches.py
Author: Farros Ramzy (you@domain.com)
Description: Autouse patches for asset route tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

import importlib
from types import SimpleNamespace

import pytest

ASSET_ROUTE_MODULES = [
    "app.routes.assets",
    "app.routes.asset_routes.asset_query_routes",
    "app.routes.asset_routes.asset_registration_routes",
    "app.routes.asset_routes.asset_lifecycle_routes",
    "app.routes.asset_routes.asset_movement_routes",
]


def patch_asset_route_attr(monkeypatch, attr_name, value):
    for module_name in ASSET_ROUTE_MODULES:
        try:
            module = importlib.import_module(module_name)
        except ModuleNotFoundError:
            continue

        if hasattr(module, attr_name):
            monkeypatch.setattr(module, attr_name, value)


def make_fake_asset():
    return SimpleNamespace(
        tag_id="TAG_ROUTE_1",
        item_name="Infusion Pump",
        status="active",
        hospital_id="HOSP_1",
        hospital_name="General Hospital",
        last_room_name="ICU",
        last_node_id="NODE_ICU",
        last_device_id="NODE_ICU",
        last_seen_at=None,
        registered_at=None,
        flow_status="available",
        expected_room_name="",
        expected_node_id="",
        assigned_room_name="ICU",
        assigned_node_id="NODE_ICU",
        active_movement_request_id=None,
        movement_note="",
        created_at=None,
        updated_at=None,
        created_by_user_id=None,
        deregistered_at=None,
        deregistered_reason="",
    )


@pytest.fixture(autouse=True)
def patch_asset_route_services(monkeypatch, patch_sessionlocal_and_side_effects):
    fake_asset = make_fake_asset()
    fake_asset_dict = {
        "tag_id": fake_asset.tag_id,
        "item_name": fake_asset.item_name,
        "status": fake_asset.status,
        "flow_status": fake_asset.flow_status,
    }

    patch_asset_route_attr(monkeypatch, "asset_to_dict", lambda asset: fake_asset_dict)
    patch_asset_route_attr(monkeypatch, "list_assets", lambda: [fake_asset])
    patch_asset_route_attr(monkeypatch, "register_asset_record", lambda *args, **kwargs: fake_asset)
    patch_asset_route_attr(monkeypatch, "deregister_asset_record", lambda *args, **kwargs: fake_asset)
    patch_asset_route_attr(monkeypatch, "delete_asset_record", lambda *args, **kwargs: {"message": "asset_deleted"})
    patch_asset_route_attr(monkeypatch, "list_asset_movement_requests", lambda status="": [])
    patch_asset_route_attr(monkeypatch, "create_asset_movement_request", lambda req, user_id: {"message": "movement_requested", "asset": fake_asset_dict, "movement_request_id": 123})
    patch_asset_route_attr(monkeypatch, "approve_asset_movement_request", lambda req, user_id: {"message": "movement_approved", "asset": fake_asset_dict, "movement_request_id": req.movement_request_id})
    patch_asset_route_attr(monkeypatch, "reject_asset_movement_request", lambda req, user_id: {"message": "movement_rejected", "asset": fake_asset_dict, "movement_request_id": req.movement_request_id})
    patch_asset_route_attr(monkeypatch, "cancel_asset_movement_request", lambda req, user_id: {"message": "movement_cancelled", "asset": fake_asset_dict, "movement_request_id": req.movement_request_id})
