"""
File: test_node_enrollment_routes.py
Author: Farros Ramzy (you@domain.com)
Description: Node enrollment route tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

import pytest

from app.routes.nodes import router as nodes_router


def test_enroll_node_requires_provisioning_key(make_route_client):
    client = make_route_client([nodes_router])

    response = client.post("/nodes/enroll", json={"device_id": "NODE_ROUTE_2"})

    assert response.status_code == 401
    assert response.json()["detail"] == "invalid_node_provisioning_key"

def test_enroll_node_succeeds_with_valid_provisioning_key(make_route_client):
    client = make_route_client([nodes_router])

    response = client.post(
        "/nodes/enroll",
        headers={"X-Device-Provisioning-Key": "test-node-key"},
        json={"device_id": "NODE_ROUTE_2"},
    )

    assert response.status_code == 200
    assert response.json()["message"] == "node_enrolled"
    assert response.json()["node"]["device_id"] == "NODE_ROUTE_2"

def test_provision_node_succeeds_with_valid_provisioning_key(make_route_client):
    client = make_route_client([nodes_router])

    response = client.post(
        "/nodes/provision",
        headers={"X-Device-Provisioning-Key": "test-node-key"},
        json={"device_id": "NODE_ROUTE_3"},
    )

    assert response.status_code == 200
    assert response.json()["is_provisioned"] is False
    assert response.json()["mqtt_port"] == 1883
