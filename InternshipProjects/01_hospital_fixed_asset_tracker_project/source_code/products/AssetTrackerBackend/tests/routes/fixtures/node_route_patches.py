"""
File: node_route_patches.py
Author: Farros Ramzy (you@domain.com)
Description: Autouse patches for node route tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

import importlib

import pytest

NODE_ROUTE_MODULES = [
    "app.routes.nodes",
    "app.routes.node_routes.node_query_routes",
    "app.routes.node_routes.node_lifecycle_routes",
    "app.routes.node_routes.node_provisioning_routes",
    "app.routes.node_routes.node_command_routes",
]


def patch_node_route_attr(monkeypatch, attr_name, value):
    for module_name in NODE_ROUTE_MODULES:
        try:
            module = importlib.import_module(module_name)
        except ModuleNotFoundError:
            continue

        if hasattr(module, attr_name):
            monkeypatch.setattr(module, attr_name, value)


def fake_node_dict(device_id="NODE_ROUTE_1"):
    return {
        "device_id": device_id,
        "alias": "Route Node",
        "role": "CHECKPOINT",
        "hospital_id": "HOSP_1",
        "hospital_name": "General Hospital",
        "room_name": "ICU",
        "mqtt_host": "localhost",
        "mqtt_port": 1883,
        "is_provisioned": True,
        "status": "ONLINE",
        "last_ping_at": None,
        "last_event_at": None,
        "last_message": "test node",
    }


@pytest.fixture(autouse=True)
def patch_node_route_services(monkeypatch, patch_sessionlocal_and_side_effects):
    fake_node = fake_node_dict()

    patch_node_route_attr(monkeypatch, "list_nodes", lambda: [fake_node])
    patch_node_route_attr(monkeypatch, "enroll_node_record", lambda device_id: fake_node_dict(device_id))
    patch_node_route_attr(monkeypatch, "get_provision_payload", lambda device_id: {"is_provisioned": False, "role": "", "hospital_id": "", "hospital_name": "", "room_name": "", "mqtt_host": "", "mqtt_port": 1883})
    patch_node_route_attr(monkeypatch, "assign_node_record", lambda device_id, req: {"message": "node_assigned", "node": {**fake_node, "device_id": device_id, "alias": req.alias}})
    patch_node_route_attr(monkeypatch, "unassign_node_record", lambda device_id: {**fake_node, "device_id": device_id, "status": "DISABLED"})
    patch_node_route_attr(monkeypatch, "delete_node_record", lambda device_id: {"message": "node_deleted", "device_id": device_id})
