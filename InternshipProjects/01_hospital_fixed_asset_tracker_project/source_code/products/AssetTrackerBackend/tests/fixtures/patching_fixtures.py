"""
File: patching_fixtures.py
Author: Farros Ramzy (you@domain.com)
Description: Autouse patches for external side effects and test DB sessions.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

import importlib

import pytest

SESSIONLOCAL_MODULES = [
    "app.database",
    "app.services.assets.asset_service",
    "app.services.assets.asset_repository",
    "app.services.assets.asset_event_service",
    "app.services.assets.asset_registration_service",
    "app.services.assets.asset_location_service",
    "app.services.assets.asset_movement_service",
    "app.services.assets.registration.asset_register_service",
    "app.services.assets.registration.asset_deregister_service",
    "app.services.assets.registration.registration_validation_service",
    "app.services.assets.location.asset_location_update_service",
    "app.services.assets.location.asset_flow_resolver",
    "app.services.assets.location.asset_movement_completion_service",
    "app.services.assets.location.asset_timestamp_service",
    "app.services.assets.movement.movement_request_create_service",
    "app.services.assets.movement.movement_decision_service",
    "app.services.assets.movement.movement_cancel_service",
    "app.services.assets.movement.movement_query_service",
    "app.services.assets.movement.movement_serializer",
    "app.services.nodes.node_service",
    "app.services.nodes.node_assigner",
    "app.services.nodes.node_status_monitor",
    "app.services.nodes.node_lifecycle_service",
    "app.services.nodes.node_queries",
    "app.services.nodes.node_reference_service",
    "app.services.mqtt.mqtt_client",
    "app.services.mqtt.mqtt_router",
    "app.services.mqtt.mqtt_publisher",
    "app.services.mqtt.mqtt_detection_handler",
    "app.services.mqtt.mqtt_node_status_handler",
    "app.services.mqtt.mqtt_registration_handler",
    "app.services.users.user_query_service",
    "app.services.users.user_create_service",
    "app.services.users.user_update_service",
    "app.services.users.user_password_service",
    "app.services.users.admin_setup_service",
    "app.routes.assets",
    "app.routes.nodes",
    "app.routes.users",
    "app.routes.asset_routes.asset_query_routes",
    "app.routes.asset_routes.asset_registration_routes",
    "app.routes.asset_routes.asset_movement_routes",
    "app.routes.asset_routes.asset_lifecycle_routes",
    "app.routes.node_routes.node_query_routes",
    "app.routes.node_routes.node_lifecycle_routes",
    "app.routes.node_routes.node_provisioning_routes",
    "app.routes.node_routes.node_command_routes",
    "app.routes.user_routes.user_query_routes",
    "app.routes.user_routes.user_create_routes",
    "app.routes.user_routes.user_update_routes",
    "app.routes.user_routes.user_password_routes",
]


def import_optional(module_name):
    try:
        return importlib.import_module(module_name)
    except ModuleNotFoundError:
        return None


def fake_blink_response(**kwargs):
    return {
        "ok": True,
        "message": "blink_command_published",
        "command_id": "test-command",
        "topic": "test-topic",
        "payload": kwargs,
    }


@pytest.fixture(autouse=True)
def patch_sessionlocal_and_side_effects(monkeypatch, TestingSessionLocal):
    def session_factory():
        return TestingSessionLocal()

    for module_name in SESSIONLOCAL_MODULES:
        module = import_optional(module_name)

        if module is None:
            continue

        if hasattr(module, "SessionLocal"):
            monkeypatch.setattr(module, "SessionLocal", session_factory)

        if hasattr(module, "schedule_broadcast"):
            monkeypatch.setattr(module, "schedule_broadcast", lambda payload: None)

    node_command_routes = import_optional("app.routes.node_routes.node_command_routes")

    if node_command_routes is not None:
        monkeypatch.setattr(
            node_command_routes,
            "publish_node_blink_command",
            fake_blink_response,
        )

    mqtt_publisher = import_optional("app.services.mqtt.mqtt_publisher")

    if mqtt_publisher is not None:
        monkeypatch.setattr(
            mqtt_publisher,
            "publish_node_blink_command",
            fake_blink_response,
        )
