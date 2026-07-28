"""
File: test_auth_session_routes.py
Author: Farros Ramzy (you@domain.com)
Description: Authentication route tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from app.db_models import User
from app.routes.auth import router as auth_router
from app.services.authority.auth_service import hash_password


def test_me_returns_current_user(make_user, make_route_client, auth_header):
    user = make_user(
        email="me@hospital.local",
        full_name="Current User",
        role="admin",
    )

    client = make_route_client([auth_router])

    response = client.get("/auth/me", headers=auth_header(user))

    assert response.status_code == 200
    assert response.json()["user"]["email"] == "me@hospital.local"
    assert response.json()["user"]["role"] == "admin"

def test_me_without_token_is_rejected(make_route_client):
    client = make_route_client([auth_router])

    response = client.get("/auth/me")

    assert response.status_code == 401
    assert response.json()["detail"] == "not_authenticated"

def test_me_with_invalid_token_is_rejected(make_route_client):
    client = make_route_client([auth_router])

    response = client.get(
        "/auth/me",
        headers={"Authorization": "Bearer invalid-token"},
    )

    assert response.status_code == 401
    assert response.json()["detail"] == "invalid_token"

def test_logout_returns_logged_out(make_route_client):
    client = make_route_client([auth_router])

    response = client.post("/auth/logout")

    assert response.status_code == 200
    assert response.json() == {"message": "logged_out"}
