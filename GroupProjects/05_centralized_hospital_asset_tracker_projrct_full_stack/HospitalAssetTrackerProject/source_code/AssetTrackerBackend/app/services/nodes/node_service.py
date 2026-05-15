"""
File: node_service.py
Author: Farros Ramzy (you@domain.com)
Description: Description
Version: 0.1
Date: 2026-04-23

Copyright (c) 2026
"""

from app.database import SessionLocal
from app.db_models import Node
from app.utils import now_wib
from app.serializers.node_serializer import node_to_dict


def list_nodes():
    db = SessionLocal()
    try:
        db_nodes = db.query(Node).all()
        return [node_to_dict(node) for node in db_nodes]
    finally:
        db.close()


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


def get_provision_payload(device_id: str):
    db = SessionLocal()
    try:
        node = db.query(Node).filter(Node.device_id == device_id).first()

        if node is None:
            node = Node(
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
                last_message="awaiting assignment",
            )
            db.add(node)
            db.commit()
            db.refresh(node)

        return {
            "is_provisioned": bool(node.is_provisioned),
            "role": node.role or "",
            "hospital_id": node.hospital_id or "",
            "hospital_name": node.hospital_name or "",
            "room_name": node.room_name or "",
            "mqtt_host": node.mqtt_host or "",
            "mqtt_port": node.mqtt_port or 1883,
        }
    finally:
        db.close()


def unassign_node_record(device_id: str):
    db = SessionLocal()
    try:
        node = db.query(Node).filter(Node.device_id == device_id).first()

        if node is None:
            return None

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
