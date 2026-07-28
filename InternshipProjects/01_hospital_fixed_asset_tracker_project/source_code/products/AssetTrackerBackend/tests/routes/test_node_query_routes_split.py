"""
File: test_node_query_routes_split.py
Author: Farros Ramzy (you@domain.com)
Description: Node query route tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

import pytest

from app.routes.nodes import router as nodes_router


def test_get_nodes_requires_authentication(make_route_client):
    client = make_route_client([nodes_router])

    response = client.get("/nodes")

    assert response.status_code == 401
    assert response.json()["detail"] == "not_authenticated"

@pytest.mark.parametrize(
    "role", ["admin", "test_user", "technician", "monitor_staff", "registration_staff"]
)
def test_get_nodes_allowed_roles(role, make_user, make_route_client, auth_header):
    user = make_user(email=f"{role}@hospital.local", full_name=role, role=role)
    client = make_route_client([nodes_router])

    response = client.get("/nodes", headers=auth_header(user))

    assert response.status_code == 200
    assert response.json()[0]["device_id"] == "NODE_ROUTE_1"

def test_get_nodes_allows_test_user(
    make_user,
    make_route_client,
    auth_header,
):
    test_user = make_user(
        email="test-user-nodes@hospital.local",
        full_name="Test User",
        role="test_user",
        is_active=True,
    )

    client = make_route_client([nodes_router])

    response = client.get(
        "/nodes",
        headers=auth_header(test_user),
    )

    assert response.status_code == 200
    assert response.json()[0]["device_id"] == "NODE_ROUTE_1"
