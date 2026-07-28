"""
File: node_assignment_guard.py
Author: Farros Ramzy (you@domain.com)
Description: Guards unsafe node re-assignment changes.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from app.db.node_db_model import Node
from app.services.nodes.assigner.node_assignment_blockers import (
    find_node_reassignment_blockers,
)
from app.services.nodes.assigner.node_assignment_change import (
    build_reassignment_context,
)


def check_node_reassignment_allowed(
    db,
    node: Node,
    new_role: str,
    new_room_name: str,
    new_hospital_id: str,
) -> dict:
    context = build_reassignment_context(
        node=node,
        new_role=new_role,
        new_room_name=new_room_name,
        new_hospital_id=new_hospital_id,
    )

    if not context["has_dangerous_change"]:
        return _allowed()

    blockers = find_node_reassignment_blockers(db, node.device_id)

    if blockers["total"] == 0:
        return _allowed()

    return _blocked(context, blockers)


def _allowed() -> dict:
    return {"allowed": True}


def _blocked(context: dict, blockers: dict) -> dict:
    old_values = context["old"]
    new_values = context["new"]

    return {
        "allowed": False,
        "message": "node_reassignment_blocked",
        "reason": "node_is_referenced_by_active_assets_or_movements",
        "device_id": context["device_id"],
        "old_role": old_values["role"],
        "new_role": new_values["role"],
        "old_room_name": old_values["room_name"],
        "new_room_name": new_values["room_name"],
        "old_hospital_id": old_values["hospital_id"],
        "new_hospital_id": new_values["hospital_id"],
        "blockers": blockers,
    }
