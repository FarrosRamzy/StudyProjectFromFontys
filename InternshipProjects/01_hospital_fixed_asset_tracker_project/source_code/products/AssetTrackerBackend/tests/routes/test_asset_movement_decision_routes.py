"""
File: test_asset_movement_decision_routes.py
Author: Farros Ramzy (you@domain.com)
Description: Asset movement route decision tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

import pytest

from app.routes.assets import router as assets_router


def test_approve_movement_rejects_monitor_staff(
    make_user, make_route_client, auth_header
):
    user = make_user(
        email="monitor@hospital.local",
        full_name="Monitor",
        role="monitor_staff",
    )
    client = make_route_client([assets_router])

    response = client.post(
        "/assets/movement/approve",
        headers=auth_header(user),
        json={"movement_request_id": 123, "registration_node_id": "REG_NODE"},
    )

    assert response.status_code == 403

def test_approve_movement_allowed_for_registration_staff(
    make_user, make_route_client, auth_header
):
    user = make_user(
        email="registration@hospital.local",
        full_name="Registration",
        role="registration_staff",
    )
    client = make_route_client([assets_router])

    response = client.post(
        "/assets/movement/approve",
        headers=auth_header(user),
        json={"movement_request_id": 123, "registration_node_id": "REG_NODE"},
    )

    assert response.status_code == 200
    assert response.json()["message"] == "movement_approved"

def test_test_user_can_approve_asset_movement(
    make_user,
    make_route_client,
    auth_header,
):
    test_user = make_user(
        email="test-user-approve-movement@hospital.local",
        full_name="Test User",
        role="test_user",
        is_active=True,
    )

    client = make_route_client([assets_router])

    response = client.post(
        "/assets/movement/approve",
        headers=auth_header(test_user),
        json={
            "movement_request_id": 1,
            "registration_node_id": "NODE_REGISTRATION",
        },
    )

    assert response.status_code == 200
    assert response.json()["message"] == "movement_approved"
