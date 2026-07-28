"""
File: test_user_create_routes_split.py
Author: Farros Ramzy (you@domain.com)
Description: User-management creation route tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from app.db_models import User
from app.routes.users import router as users_router
from app.services.authority.auth_service import verify_password


def test_post_users_creates_user_for_admin(
    db_session, make_user, make_route_client, auth_header
):
    admin = make_user(
        email="admin@hospital.local",
        full_name="System Admin",
        role="admin",
    )

    client = make_route_client([users_router])

    response = client.post(
        "/users",
        headers=auth_header(admin),
        json={
            "email": "New.User@Hospital.Local",
            "full_name": "New User",
            "role": "monitor_staff",
            "password": "Monitor12345!",
        },
    )

    assert response.status_code == 201

    data = response.json()
    assert data["message"] == "user_created"
    assert data["user"]["email"] == "new.user@hospital.local"
    assert data["user"]["role"] == "monitor_staff"

    created_user = (
        db_session.query(User).filter(User.email == "new.user@hospital.local").first()
    )

    assert created_user is not None
    assert verify_password("Monitor12345!", created_user.hashed_password)

def test_post_users_can_create_test_user_for_admin(
    db_session, make_user, make_route_client, auth_header
):
    admin = make_user(
        email="admin-create-test-user@hospital.local",
        full_name="System Admin",
        role="admin",
    )

    client = make_route_client([users_router])

    response = client.post(
        "/users",
        headers=auth_header(admin),
        json={
            "email": "test.user@hospital.local",
            "full_name": "Test User",
            "role": "test_user",
            "password": "TestUser12345!",
        },
    )

    assert response.status_code == 201

    data = response.json()
    assert data["message"] == "user_created"
    assert data["user"]["email"] == "test.user@hospital.local"
    assert data["user"]["role"] == "test_user"

def test_post_users_rejects_duplicate_email(make_user, make_route_client, auth_header):
    admin = make_user(
        email="admin@hospital.local",
        full_name="System Admin",
        role="admin",
    )
    make_user(
        email="duplicate@hospital.local",
        full_name="Duplicate User",
        role="monitor_staff",
    )

    client = make_route_client([users_router])

    response = client.post(
        "/users",
        headers=auth_header(admin),
        json={
            "email": "duplicate@hospital.local",
            "full_name": "Duplicate User 2",
            "role": "technician",
            "password": "Technician12345!",
        },
    )

    assert response.status_code == 409
    assert response.json()["detail"] == "email_already_registered"

def test_post_users_rejects_invalid_role(make_user, make_route_client, auth_header):
    admin = make_user(
        email="admin@hospital.local",
        full_name="System Admin",
        role="admin",
    )

    client = make_route_client([users_router])

    response = client.post(
        "/users",
        headers=auth_header(admin),
        json={
            "email": "visitor@hospital.local",
            "full_name": "Visitor User",
            "role": "visitor",
            "password": "Visitor12345!",
        },
    )

    assert response.status_code == 400
    assert response.json()["detail"] == "invalid_role"
