"""
File: test_node_command_routes_split.py
Author: Farros Ramzy (you@domain.com)
Description: Node route command tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

import pytest

from app.routes.nodes import router as nodes_router


def test_identify_node_success_for_technician(
    make_node, make_user, make_route_client, auth_header
):
    make_node(
        device_id="NODE_IDENTIFY",
        role="CHECKPOINT",
        hospital_id="HOSP_1",
        hospital_name="General Hospital",
        room_name="ICU",
        status="ONLINE",
        is_provisioned=True,
    )

    user = make_user(
        email="tech@hospital.local",
        full_name="Technician",
        role="technician",
    )
    client = make_route_client([nodes_router])

    response = client.post(
        "/nodes/NODE_IDENTIFY/identify",
        headers=auth_header(user),
        json={"blink_count": 6, "interval_ms": 150},
    )

    assert response.status_code == 200
    assert response.json()["message"] == "blink_command_sent"
