"""
File: test_asset_movement_request_routes.py
Author: Farros Ramzy (you@domain.com)
Description: Asset route movement tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

import pytest

from app.routes.assets import router as assets_router


@pytest.mark.parametrize(
    "role", ["admin", "test_user", "registration_staff", "monitor_staff"]
)
def test_request_movement_allowed_roles(
    role, make_user, make_route_client, auth_header
):
    user = make_user(email=f"{role}@hospital.local", full_name=role, role=role)
    client = make_route_client([assets_router])

    response = client.post(
        "/assets/movement/request",
        headers=auth_header(user),
        json={
            "tag_id": "TAG_ROUTE_1",
            "destination_room_name": "ER",
            "destination_node_id": "NODE_ER",
            "note": "Move to ER",
        },
    )

    assert response.status_code == 200
    assert response.json()["message"] == "movement_requested"

def test_test_user_can_request_asset_movement(
    make_user,
    make_route_client,
    auth_header,
):
    test_user = make_user(
        email="test-user-movement@hospital.local",
        full_name="Test User",
        role="test_user",
        is_active=True,
    )

    client = make_route_client([assets_router])

    response = client.post(
        "/assets/movement/request",
        headers=auth_header(test_user),
        json={
            "tag_id": "TAG_ROUTE_1",
            "destination_room_name": "ER",
            "destination_node_id": "NODE_ER",
            "note": "Move to ER",
        },
    )

    assert response.status_code == 200
    assert response.json()["message"] == "movement_requested"
