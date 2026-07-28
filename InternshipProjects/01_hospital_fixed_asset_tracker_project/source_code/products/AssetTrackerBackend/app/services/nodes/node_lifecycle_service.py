"""
File: node_lifecycle_service.py
Author: Farros Ramzy (you@domain.com)
Description: Node lifecycle operations: enroll, unassign, delete.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from app.database import SessionLocal
from app.db_models import Node
from app.serializers.node_serializer import node_to_dict
from app.utils import now_wib
from app.services.nodes.node_reference_service import find_node_reference_blockers


def enroll_node_record(device_id: str):
    db = SessionLocal()
    try:
        node = db.query(Node).filter(Node.device_id == device_id).first()

        if not node:
            node = Node(
                device_id=device_id,
                role="",
                hospital_name="",
                room_name="",
                mqtt_host="",
                mqtt_port=1883,
                is_provisioned=False,
                status="DISCOVERED",
                last_ping_at=None,
                last_event_at=now_wib(),
                last_message="awaiting assignment",
            )
        else:
            if not node.status:
                node.status = "DISCOVERED"
            node.last_event_at = now_wib()
            node.last_message = "awaiting assignment"

        db.add(node)
        db.commit()
        db.refresh(node)

        return node_to_dict(node)
    finally:
        db.close()


def unassign_node_record(device_id: str):
    db = SessionLocal()
    try:
        node = db.query(Node).filter(Node.device_id == device_id).first()

        if node is None:
            return None

        blockers = find_node_reference_blockers(db, device_id)

        if blockers["total"] > 0:
            return {
                "message": "node_unassign_blocked",
                "reason": "node_is_referenced_by_active_assets_or_movements",
                "device_id": device_id,
                "blockers": blockers,
            }

        node.alias = ""
        node.role = ""
        node.hospital_name = ""
        node.room_name = ""
        node.mqtt_host = ""
        node.mqtt_port = 1883
        node.is_provisioned = False
        node.status = "DISABLED"
        node.last_event_at = now_wib()
        node.last_message = "node unassigned by user"

        db.add(node)
        db.commit()
        db.refresh(node)

        return node_to_dict(node)

    finally:
        db.close()


def delete_node_record(device_id: str):
    db = SessionLocal()
    try:
        node = db.query(Node).filter(Node.device_id == device_id).first()

        if node is None:
            return {"message": "node_not_found"}

        if node.is_provisioned and node.status != "DISABLED":
            return {"message": "node_must_be_unassigned_first"}

        db.delete(node)
        db.commit()

        return {
            "message": "node_deleted",
            "device_id": device_id,
        }

    finally:
        db.close()
