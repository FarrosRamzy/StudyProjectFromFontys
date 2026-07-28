"""
File: test_user_password_routes.py
Author: Farros Ramzy (you@domain.com)
Description: Route tests for password management.
Version: 0.1
Date: 2026-06-04

Copyright (c) 2026
"""

from app.routes.users import router as users_router
from app.services.authority.auth_service import verify_password


def test_current_user_can_change_own_password(
    db_session,
    make_route_client,
    make_user,
    auth_header,
):
    user = make_user(
        email="staff@test.local",
        role="registration_staff",
        password="OldPassword123!",
    )
    client = make_route_client([users_router])

    response = client.post(
        "/users/me/password",
        headers=auth_header(user),
        json={
            "current_password": "OldPassword123!",
            "new_password": "NewPassword123!",
        },
    )

    assert response.status_code == 200
    assert response.json()["message"] == "password_changed"
    db_session.refresh(user)
    assert verify_password("NewPassword123!", user.hashed_password)


def test_current_user_password_change_rejects_wrong_password(
    make_route_client,
    make_user,
    auth_header,
):
    user = make_user(password="OldPassword123!")
    client = make_route_client([users_router])

    response = client.post(
        "/users/me/password",
        headers=auth_header(user),
        json={
            "current_password": "WrongPassword123!",
            "new_password": "NewPassword123!",
        },
    )

    assert response.status_code == 400
    assert response.json()["detail"] == "current_password_incorrect"


def test_admin_can_reset_another_user_password(
    db_session,
    make_route_client,
    make_user,
    auth_header,
):
    admin = make_user(email="admin@test.local", role="admin")
    staff = make_user(
        email="staff@test.local",
        role="technician",
        password="OldPassword123!",
    )
    client = make_route_client([users_router])

    response = client.post(
        f"/users/{staff.id}/reset-password",
        headers=auth_header(admin),
        json={"password": "ResetPassword123!"},
    )

    assert response.status_code == 200
    assert response.json()["message"] == "user_password_reset"
    db_session.refresh(staff)
    assert verify_password("ResetPassword123!", staff.hashed_password)


def test_non_admin_cannot_reset_user_password(
    make_route_client,
    make_user,
    auth_header,
):
    staff = make_user(email="staff@test.local", role="technician")
    target = make_user(email="target@test.local", role="monitor_staff")
    client = make_route_client([users_router])

    response = client.post(
        f"/users/{target.id}/reset-password",
        headers=auth_header(staff),
        json={"password": "ResetPassword123!"},
    )

    assert response.status_code == 403
