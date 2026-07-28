"""
File: test_user_create_permission_routes.py
Author: Farros Ramzy (you@domain.com)
Description: User-management creation permission route tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from app.db_models import User
from app.routes.users import router as users_router
from app.services.authority.auth_service import verify_password


def test_test_user_cannot_create_user(
    make_user,
    make_route_client,
    auth_header,
):
    test_user = make_user(
        email="test-user-create@hospital.local",
        full_name="Test User",
        role="test_user",
        is_active=True,
    )

    client = make_route_client([users_router])

    response = client.post(
        "/users",
        headers=auth_header(test_user),
        json={
            "email": "new.user@hospital.local",
            "full_name": "New User",
            "role": "monitor_staff",
            "password": "Password12345!",
        },
    )

    assert response.status_code == 403
    assert response.json()["detail"] == "insufficient_permission"
