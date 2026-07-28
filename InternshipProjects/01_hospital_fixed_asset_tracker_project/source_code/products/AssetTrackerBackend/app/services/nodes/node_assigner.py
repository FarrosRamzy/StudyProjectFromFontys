"""
File: node_assigner.py
Author: Farros Ramzy (you@domain.com)
Description: Node assignment and re-assignment service.
Version: 0.2
Date: 2026-05-22
"""

from app.database import SessionLocal
from app.serializers.node_serializer import node_to_dict
from app.services.nodes.assigner.node_assignment_guard import (
    check_node_reassignment_allowed,
)
from app.services.nodes.assigner.node_assignment_payload import (
    build_node_assignment_payload,
)
from app.services.nodes.assigner.node_assignment_repository import (
    get_or_create_assignable_node,
    save_node_assignment,
)
from app.services.nodes.assigner.node_assignment_writer import apply_assignment_payload


def assign_node_record(device_id: str, req):
    db = SessionLocal()

    try:
        node = get_or_create_assignable_node(db, device_id)

        payload, error = build_node_assignment_payload(req)
        if error:
            return error

        reassignment_error = _get_reassignment_error(db, node, payload)
        if reassignment_error:
            return reassignment_error

        assigned_node = apply_assignment_payload(node, payload)
        saved_node = save_node_assignment(db, assigned_node)

        return {
            "message": "node_assigned",
            "node": node_to_dict(saved_node),
        }

    finally:
        db.close()


def _get_reassignment_error(db, node, payload):
    if not node.is_provisioned:
        return None

    result = check_node_reassignment_allowed(
        db=db,
        node=node,
        new_role=payload["role"],
        new_room_name=payload["room_name"],
        new_hospital_id=payload["hospital_id"],
    )

    if result["allowed"]:
        return None

    return result
