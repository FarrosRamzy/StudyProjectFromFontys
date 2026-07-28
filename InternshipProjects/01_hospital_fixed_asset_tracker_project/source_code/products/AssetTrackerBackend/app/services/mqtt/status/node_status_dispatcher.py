"""
File: node_status_dispatcher.py
Author: Farros Ramzy (you@domain.com)
Description: Routes MQTT node status payloads to the right status case.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from app.services.mqtt.status.node_status_cases import (
    handle_offline_node,
    handle_online_node,
    handle_unknown_status_node,
)
from app.services.mqtt.status.node_status_payload import (
    is_offline_status,
    is_online_status,
)


def handle_provisioned_node_status(db, node, status_payload: dict) -> None:
    if is_online_status(status_payload["status"]):
        handle_online_node(db, node, status_payload)
        return

    if is_offline_status(status_payload["status"]):
        handle_offline_node(db, node, status_payload)
        return

    handle_unknown_status_node(db, node, status_payload)
