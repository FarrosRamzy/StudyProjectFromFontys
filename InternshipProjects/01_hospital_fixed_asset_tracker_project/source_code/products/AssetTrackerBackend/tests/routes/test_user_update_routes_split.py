"""
File: test_user_update_routes_split.py
Author: Farros Ramzy (you@domain.com)
Description: User-management update route tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from app.db_models import User
from app.routes.users import router as users_router
from app.services.authority.auth_service import verify_password


def test_patch_user_role_succeeds_for_admin(make_user, make_route_client, auth_header):
    admin = make_user(
        email="admin@hospital.local",
        full_name="System Admin",
        role="admin",
    )
    target_user = make_user(
        email="target@hospital.local",
        full_name="Target User",
        role="monitor_staff",
    )

    client = make_route_client([users_router])

    response = client.patch(
        f"/users/{target_user.id}/role",
        headers=auth_header(admin),
        json={"role": "technician"},
    )

    assert response.status_code == 200
    assert response.json()["message"] == "user_role_updated"
    assert response.json()["user"]["role"] == "technician"

def test_patch_user_active_blocks_admin_self_deactivation(
    make_user, make_route_client, auth_header
):
    admin = make_user(
        email="admin@hospital.local",
        full_name="System Admin",
        role="admin",
    )

    client = make_route_client([users_router])

    response = client.patch(
        f"/users/{admin.id}/active",
        headers=auth_header(admin),
        json={"is_active": False},
    )

    assert response.status_code == 400
    assert response.json()["detail"] == "admin_cannot_deactivate_self"

def test_patch_user_active_deactivates_other_user(
    make_user, make_route_client, auth_header
):
    admin = make_user(
        email="admin@hospital.local",
        full_name="System Admin",
        role="admin",
    )
    target_user = make_user(
        email="target@hospital.local",
        full_name="Target User",
        role="monitor_staff",
        is_active=True,
    )

    client = make_route_client([users_router])

    response = client.patch(
        f"/users/{target_user.id}/active",
        headers=auth_header(admin),
        json={"is_active": False},
    )

    assert response.status_code == 200
    assert response.json()["message"] == "user_active_status_updated"
    assert response.json()["user"]["is_active"] is False
