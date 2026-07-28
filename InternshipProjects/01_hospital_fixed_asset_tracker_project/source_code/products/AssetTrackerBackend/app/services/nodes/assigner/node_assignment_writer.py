"""
File: node_assignment_writer.py
Author: Farros Ramzy (you@domain.com)
Description: Applies assignment payload data to Node model.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from app.db.node_db_model import Node
from app.utils import now_wib


def apply_assignment_payload(node: Node, payload: dict) -> Node:
    node.alias = payload["alias"]
    node.role = payload["role"]
    node.hospital_id = payload["hospital_id"]
    node.hospital_name = payload["hospital_name"]
    node.room_name = payload["room_name"]
    node.mqtt_host = payload["mqtt_host"]
    node.mqtt_port = payload["mqtt_port"]

    node.is_provisioned = True
    node.status = "ASSIGNED"
    node.last_event_at = now_wib()
    node.last_message = "configuration assigned"

    return node
