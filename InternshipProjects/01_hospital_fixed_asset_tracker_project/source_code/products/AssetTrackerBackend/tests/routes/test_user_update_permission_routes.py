"""
File: test_user_update_permission_routes.py
Author: Farros Ramzy (you@domain.com)
Description: User-management update permission route tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from app.db_models import User
from app.routes.users import router as users_router
from app.services.authority.auth_service import verify_password


def test_test_user_cannot_deactivate_user(
    make_user,
    make_route_client,
    auth_header,
):
    test_user = make_user(
        email="test-user-deactivate@hospital.local",
        full_name="Test User",
        role="test_user",
        is_active=True,
    )

    target_user = make_user(
        email="target-user@hospital.local",
        full_name="Target User",
        role="monitor_staff",
        is_active=True,
    )

    client = make_route_client([users_router])

    response = client.patch(
        f"/users/{target_user.id}/active",
        headers=auth_header(test_user),
        json={"is_active": False},
    )

    assert response.status_code == 403
    assert response.json()["detail"] == "insufficient_permission"

def test_test_user_cannot_update_user_role(
    make_user,
    make_route_client,
    auth_header,
):
    test_user = make_user(
        email="test-user-role-update@hospital.local",
        full_name="Test User",
        role="test_user",
        is_active=True,
    )

    target_user = make_user(
        email="target-role-update@hospital.local",
        full_name="Target User",
        role="monitor_staff",
        is_active=True,
    )

    client = make_route_client([users_router])

    response = client.patch(
        f"/users/{target_user.id}/role",
        headers=auth_header(test_user),
        json={"role": "technician"},
    )

    assert response.status_code == 403
    assert response.json()["detail"] == "insufficient_permission"
