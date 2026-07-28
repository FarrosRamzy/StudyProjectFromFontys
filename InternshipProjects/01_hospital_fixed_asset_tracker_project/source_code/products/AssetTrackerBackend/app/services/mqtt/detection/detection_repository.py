"""
File: detection_repository.py
Author: Farros Ramzy (you@domain.com)
Description: Database helpers for MQTT detection handling.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from app.db.node_db_model import Node


def find_node_by_device_id(db, device_id: str):
    return db.query(Node).filter(Node.device_id == device_id).first()
