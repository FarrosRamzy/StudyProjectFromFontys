"""
File: test_auth_login_routes.py
Author: Farros Ramzy (you@domain.com)
Description: Login authentication route tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from app.db_models import User
from app.routes.auth import router as auth_router
from app.services.authority.auth_service import hash_password


def test_login_success_returns_token_and_user(db_session, make_route_client):
    user = User(
        email="admin@hospital.local",
        full_name="System Administrator",
        role="admin",
        hashed_password=hash_password("Admin12345!"),
        is_active=True,
    )
    db_session.add(user)
    db_session.commit()

    client = make_route_client([auth_router])

    response = client.post(
        "/auth/login",
        json={
            "email": "admin@hospital.local",
            "password": "Admin12345!",
        },
    )

    assert response.status_code == 200

    data = response.json()

    assert data["access_token"]
    assert data["token_type"] == "bearer"
    assert data["user"]["email"] == "admin@hospital.local"
    assert data["user"]["role"] == "admin"

def test_login_normalizes_email_before_authentication(db_session, make_route_client):
    user = User(
        email="monitor@hospital.local",
        full_name="Monitor User",
        role="monitor_staff",
        hashed_password=hash_password("Monitor12345!"),
        is_active=True,
    )
    db_session.add(user)
    db_session.commit()

    client = make_route_client([auth_router])

    response = client.post(
        "/auth/login",
        json={
            "email": "  MONITOR@Hospital.Local  ",
            "password": "Monitor12345!",
        },
    )

    assert response.status_code == 200
    assert response.json()["user"]["email"] == "monitor@hospital.local"

def test_login_fails_with_wrong_password(db_session, make_route_client):
    user = User(
        email="admin@hospital.local",
        full_name="System Administrator",
        role="admin",
        hashed_password=hash_password("Admin12345!"),
        is_active=True,
    )
    db_session.add(user)
    db_session.commit()

    client = make_route_client([auth_router])

    response = client.post(
        "/auth/login",
        json={
            "email": "admin@hospital.local",
            "password": "WrongPassword123!",
        },
    )

    assert response.status_code == 401
    assert response.json()["detail"] == "invalid_email_or_password"

def test_login_fails_for_inactive_user(db_session, make_route_client):
    user = User(
        email="inactive@hospital.local",
        full_name="Inactive User",
        role="monitor_staff",
        hashed_password=hash_password("Inactive12345!"),
        is_active=False,
    )
    db_session.add(user)
    db_session.commit()

    client = make_route_client([auth_router])

    response = client.post(
        "/auth/login",
        json={
            "email": "inactive@hospital.local",
            "password": "Inactive12345!",
        },
    )

    assert response.status_code == 401
    assert response.json()["detail"] == "invalid_email_or_password"
