"""
File: test_asset_delete_routes.py
Author: Farros Ramzy (you@domain.com)
Description: Asset route deletion tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

import pytest

from app.routes.assets import router as assets_router


def test_delete_asset_rejects_monitor_staff(make_user, make_route_client, auth_header):
    user = make_user(
        email="monitor@hospital.local",
        full_name="Monitor",
        role="monitor_staff",
    )
    client = make_route_client([assets_router])

    response = client.delete("/assets/TAG_ROUTE_1", headers=auth_header(user))

    assert response.status_code == 403

def test_delete_asset_allowed_for_admin(make_user, make_route_client, auth_header):
    user = make_user(
        email="admin@hospital.local",
        full_name="Admin",
        role="admin",
    )
    client = make_route_client([assets_router])

    response = client.delete("/assets/TAG_ROUTE_1", headers=auth_header(user))

    assert response.status_code == 200
    assert response.json()["message"] == "asset_deleted"
