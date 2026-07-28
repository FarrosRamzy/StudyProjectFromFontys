"""
File: test_admin_account_safety_policy_routes.py
Author: Farros Ramzy (you@domain.com)
Description: Route tests for admin account safety policy.
Version: 0.1
Date: 2026-06-05

Copyright (c) 2026
"""

from app.routes.users import router as users_router


def test_admin_cannot_disable_self(make_user, make_route_client, auth_header):
    admin = make_user(email="admin@hospital.local", role="admin", is_active=True)
    make_user(email="staff@hospital.local", role="monitor_staff")
    client = make_route_client([users_router])

    response = client.patch(
        f"/users/{admin.id}/active",
        headers=auth_header(admin),
        json={"is_active": False},
    )

    assert response.status_code == 400
    assert response.json()["detail"] == "admin_cannot_deactivate_self"


def test_admin_can_disable_staff(make_user, make_route_client, auth_header):
    admin = make_user(email="admin@hospital.local", role="admin", is_active=True)
    staff = make_user(email="staff@hospital.local", role="monitor_staff")
    client = make_route_client([users_router])

    response = client.patch(
        f"/users/{staff.id}/active",
        headers=auth_header(admin),
        json={"is_active": False},
    )

    assert response.status_code == 200
    assert response.json()["user"]["is_active"] is False


def test_admin_cannot_change_own_role(make_user, make_route_client, auth_header):
    admin = make_user(email="admin@hospital.local", role="admin", is_active=True)
    client = make_route_client([users_router])

    response = client.patch(
        f"/users/{admin.id}/role",
        headers=auth_header(admin),
        json={"role": "technician"},
    )

    assert response.status_code == 400
    assert response.json()["detail"] == "cannot_change_own_role"


def test_admin_can_demote_another_admin_when_one_active_admin_remains(
    make_user,
    make_route_client,
    auth_header,
):
    current = make_user(
        email="current@hospital.local",
        role="admin",
        is_active=True,
    )
    target = make_user(
        email="target@hospital.local",
        role="admin",
        is_active=True,
    )
    client = make_route_client([users_router])

    response = client.patch(
        f"/users/{target.id}/role",
        headers=auth_header(current),
        json={"role": "technician"},
    )

    assert response.status_code == 200
    assert response.json()["user"]["role"] == "technician"


def test_admin_cannot_reset_own_password_here(
    make_user,
    make_route_client,
    auth_header,
):
    admin = make_user(email="admin@hospital.local", role="admin", is_active=True)
    client = make_route_client([users_router])

    response = client.post(
        f"/users/{admin.id}/reset-password",
        headers=auth_header(admin),
        json={"password": "Password12345!"},
    )

    assert response.status_code == 400
    assert response.json()["detail"] == "cannot_reset_own_password_here"