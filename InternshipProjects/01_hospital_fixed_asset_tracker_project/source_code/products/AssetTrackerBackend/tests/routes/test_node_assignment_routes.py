"""
File: test_node_assignment_routes.py
Author: Farros Ramzy (you@domain.com)
Description: Node route assignment tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

import pytest

from app.routes.nodes import router as nodes_router


@pytest.mark.parametrize("role", ["admin", "technician"])
def test_assign_node_allowed_roles(role, make_user, make_route_client, auth_header):
    user = make_user(email=f"{role}@hospital.local", full_name=role, role=role)
    client = make_route_client([nodes_router])

    response = client.post(
        "/nodes/NODE_ROUTE_1/assign",
        headers=auth_header(user),
        json={
            "alias": "Assigned Node",
            "role": "CHECKPOINT",
            "hospital_id": "HOSP_1",
            "hospital_name": "General Hospital",
            "room_name": "ICU",
            "mqtt_host": "localhost",
            "mqttPort": 1883,
        },
    )

    assert response.status_code == 200
    assert response.json()["message"] == "node_assigned"

def test_assign_node_rejects_monitor_staff(make_user, make_route_client, auth_header):
    user = make_user(
        email="monitor@hospital.local",
        full_name="Monitor",
        role="monitor_staff",
    )
    client = make_route_client([nodes_router])

    response = client.post(
        "/nodes/NODE_ROUTE_1/assign",
        headers=auth_header(user),
        json={
            "alias": "Assigned Node",
            "role": "CHECKPOINT",
            "hospital_id": "HOSP_1",
            "hospital_name": "General Hospital",
            "room_name": "ICU",
            "mqtt_host": "localhost",
            "mqttPort": 1883,
        },
    )

    assert response.status_code == 403

def test_unassign_node_allowed_for_technician(
    make_user, make_route_client, auth_header
):
    user = make_user(
        email="tech@hospital.local",
        full_name="Technician",
        role="technician",
    )
    client = make_route_client([nodes_router])

    response = client.post("/nodes/NODE_ROUTE_1/unassign", headers=auth_header(user))

    assert response.status_code == 200
    assert response.json()["message"] == "node_unassigned"

def test_delete_node_allowed_for_admin(make_user, make_route_client, auth_header):
    user = make_user(
        email="admin@hospital.local",
        full_name="Admin",
        role="admin",
    )
    client = make_route_client([nodes_router])

    response = client.delete("/nodes/NODE_ROUTE_1", headers=auth_header(user))

    assert response.status_code == 200
    assert response.json()["message"] == "node_deleted"
