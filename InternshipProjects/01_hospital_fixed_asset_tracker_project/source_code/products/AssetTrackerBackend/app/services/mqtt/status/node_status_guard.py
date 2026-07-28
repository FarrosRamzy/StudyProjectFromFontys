"""
File: node_status_guard.py
Author: Farros Ramzy (you@domain.com)
Description: Guard checks for MQTT node status handling.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""


def is_missing_device_id(status_payload: dict) -> bool:
    return not status_payload["device_id"]


def is_disabled_node(node) -> bool:
    return node.status == "DISABLED"


def has_hospital_mismatch(node, status_payload: dict) -> bool:
    payload_hospital_id = status_payload["hospital_id"]

    return bool(
        node.hospital_id
        and payload_hospital_id
        and node.hospital_id != payload_hospital_id
    )


def is_unprovisioned_node(node) -> bool:
    return not node.is_provisioned
