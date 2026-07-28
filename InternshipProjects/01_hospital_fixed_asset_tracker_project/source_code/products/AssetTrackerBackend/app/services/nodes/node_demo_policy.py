"""
File: node_demo_policy.py
Author: Farros Ramzy (you@domain.com)
Description: Demo-node policy helpers.
Version: 0.1
Date: 2026-06-08

Copyright (c) 2026
"""

import os


def get_dummy_node_prefix() -> str:
    return os.getenv("DUMMY_NODE_PREFIX", "IH-DMY-NODE-").strip().upper()


def dummy_nodes_stay_online_enabled() -> bool:
    return os.getenv("DUMMY_NODES_STAY_ONLINE", "true").strip().lower() == "true"


def normalize_text(value) -> str:
    return str(value or "").strip().upper()


def is_dummy_node_device(device_id: str | None) -> bool:
    return normalize_text(device_id).startswith(get_dummy_node_prefix())


def should_skip_offline_timeout(node) -> bool:
    if not dummy_nodes_stay_online_enabled():
        return False

    return is_dummy_node_device(getattr(node, "device_id", ""))
