"""
File: test_user_password_reset_routes.py
Author: Farros Ramzy (you@domain.com)
Description: User-management password-reset route tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from app.db_models import User
from app.routes.users import router as users_router
from app.services.authority.auth_service import verify_password


def test_reset_user_password_succeeds_for_admin(
    db_session, make_user, make_route_client, auth_header
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
    )

    client = make_route_client([users_router])

    response = client.post(
        f"/users/{target_user.id}/reset-password",
        headers=auth_header(admin),
        json={"password": "NewPassword12345!"},
    )

    assert response.status_code == 200
    assert response.json()["message"] == "user_password_reset"

    db_session.refresh(target_user)
    assert verify_password("NewPassword12345!", target_user.hashed_password)
