"""
File: test_asset_query_routes_split.py
Author: Farros Ramzy (you@domain.com)
Description: Asset query route tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

import pytest

from app.routes.assets import router as assets_router


def test_get_assets_requires_authentication(make_route_client):
    client = make_route_client([assets_router])

    response = client.get("/assets")

    assert response.status_code == 401
    assert response.json()["detail"] == "not_authenticated"

@pytest.mark.parametrize(
    "role", ["admin", "test_user", "registration_staff", "monitor_staff"]
)
def test_get_assets_allowed_roles(role, make_user, make_route_client, auth_header):
    user = make_user(email=f"{role}@hospital.local", full_name=role, role=role)
    client = make_route_client([assets_router])

    response = client.get("/assets", headers=auth_header(user))

    assert response.status_code == 200
    assert response.json()[0]["tag_id"] == "TAG_ROUTE_1"

def test_get_assets_rejects_technician(make_user, make_route_client, auth_header):
    user = make_user(
        email="tech@hospital.local",
        full_name="Technician",
        role="technician",
    )
    client = make_route_client([assets_router])

    response = client.get("/assets", headers=auth_header(user))

    assert response.status_code == 403
    assert response.json()["detail"] == "insufficient_permission"
