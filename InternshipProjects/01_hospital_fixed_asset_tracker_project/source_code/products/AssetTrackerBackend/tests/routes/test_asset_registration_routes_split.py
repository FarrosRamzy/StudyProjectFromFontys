"""
File: test_asset_registration_routes_split.py
Author: Farros Ramzy (you@domain.com)
Description: Asset registration route tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

import pytest

from app.routes.assets import router as assets_router


@pytest.mark.parametrize("role", ["admin", "test_user", "registration_staff"])
def test_register_asset_allowed_roles(role, make_user, make_route_client, auth_header):
    user = make_user(email=f"{role}@hospital.local", full_name=role, role=role)
    client = make_route_client([assets_router])

    response = client.post(
        "/assets/register",
        headers=auth_header(user),
        json={
            "tag_id": "TAG_ROUTE_1",
            "item_name": "Infusion Pump",
            "registration_node_id": "REG_NODE",
            "initial_room_name": "ICU",
            "initial_node_id": "NODE_ICU",
        },
    )

    assert response.status_code == 200
    assert response.json()["message"] == "registered"

@pytest.mark.parametrize("role", ["monitor_staff", "technician"])
def test_register_asset_rejects_unauthorized_roles(
    role, make_user, make_route_client, auth_header
):
    user = make_user(email=f"{role}@hospital.local", full_name=role, role=role)
    client = make_route_client([assets_router])

    response = client.post(
        "/assets/register",
        headers=auth_header(user),
        json={
            "tag_id": "TAG_ROUTE_1",
            "item_name": "Infusion Pump",
            "registration_node_id": "REG_NODE",
            "initial_room_name": "ICU",
            "initial_node_id": "NODE_ICU",
        },
    )

    assert response.status_code == 403
