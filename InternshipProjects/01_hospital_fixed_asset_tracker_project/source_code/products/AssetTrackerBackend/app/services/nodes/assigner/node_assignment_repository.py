"""
File: node_assignment_repository.py
Author: Farros Ramzy (you@domain.com)
Description: Database helpers for node assignment.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from app.db.node_db_model import Node
from app.utils import now_wib


def get_or_create_assignable_node(db, device_id: str) -> Node:
    node = db.query(Node).filter(Node.device_id == device_id).first()

    if node:
        return node

    return _build_discovered_node(device_id)


def save_node_assignment(db, node: Node) -> Node:
    db.add(node)
    db.commit()
    db.refresh(node)

    return node


def _build_discovered_node(device_id: str) -> Node:
    return Node(
        device_id=device_id,
        role="",
        hospital_id="",
        hospital_name="",
        room_name="",
        mqtt_host="",
        mqtt_port=1883,
        is_provisioned=False,
        status="DISCOVERED",
        last_ping_at=None,
        last_event_at=now_wib(),
        last_message="created during assignment",
    )
