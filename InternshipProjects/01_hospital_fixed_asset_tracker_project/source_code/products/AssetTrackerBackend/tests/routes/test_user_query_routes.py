"""
File: test_user_query_routes.py
Author: Farros Ramzy (you@domain.com)
Description: User-management query route tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from app.db_models import User
from app.routes.users import router as users_router
from app.services.authority.auth_service import verify_password


def test_get_users_requires_authentication(make_route_client):
    client = make_route_client([users_router])

    response = client.get("/users")

    assert response.status_code == 401
    assert response.json()["detail"] == "not_authenticated"

def test_get_users_requires_admin_role(make_user, make_route_client, auth_header):
    monitor_user = make_user(
        email="monitor@hospital.local",
        full_name="Monitor User",
        role="monitor_staff",
    )

    client = make_route_client([users_router])

    response = client.get("/users", headers=auth_header(monitor_user))

    assert response.status_code == 403
    assert response.json()["detail"] == "insufficient_permission"

def test_get_users_succeeds_for_admin(make_user, make_route_client, auth_header):
    admin = make_user(
        email="admin@hospital.local",
        full_name="System Admin",
        role="admin",
    )
    make_user(
        email="technician@hospital.local",
        full_name="Technician User",
        role="technician",
    )

    client = make_route_client([users_router])

    response = client.get("/users", headers=auth_header(admin))

    assert response.status_code == 200

    emails = [user["email"] for user in response.json()]
    assert "admin@hospital.local" in emails
    assert "technician@hospital.local" in emails

def test_get_users_rejects_test_user(make_user, make_route_client, auth_header):
    test_user = make_user(
        email="test-user@hospital.local",
        full_name="Test User",
        role="test_user",
    )

    client = make_route_client([users_router])

    response = client.get(
        "/users",
        headers=auth_header(test_user),
    )

    assert response.status_code == 403
    assert response.json()["detail"] == "insufficient_permission"
