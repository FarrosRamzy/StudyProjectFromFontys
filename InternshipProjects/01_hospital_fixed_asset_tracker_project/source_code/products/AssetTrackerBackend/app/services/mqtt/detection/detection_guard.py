"""
File: detection_guard.py
Author: Farros Ramzy (you@domain.com)
Description: Guard checks for MQTT detection source nodes.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""


def is_disabled_or_unprovisioned_node(node) -> bool:
    return node.status == "DISABLED" or not node.is_provisioned


def is_non_checkpoint_node(node) -> bool:
    return node.role != "CHECKPOINT"


def has_hospital_mismatch(node, detection_payload: dict) -> bool:
    payload_hospital_id = detection_payload["hospital_id"]

    return bool(
        node.hospital_id
        and payload_hospital_id
        and node.hospital_id != payload_hospital_id
    )
