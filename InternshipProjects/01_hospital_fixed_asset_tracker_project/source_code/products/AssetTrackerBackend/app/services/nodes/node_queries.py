"""
File: node_queries.py
Author: Farros Ramzy (you@domain.com)
Description: Node query/read operations.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from app.database import SessionLocal
from app.db_models import Node
from app.serializers.node_serializer import node_to_dict
from app.utils import now_wib


def list_nodes():
    db = SessionLocal()
    try:
        db_nodes = db.query(Node).all()
        return [node_to_dict(node) for node in db_nodes]
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
