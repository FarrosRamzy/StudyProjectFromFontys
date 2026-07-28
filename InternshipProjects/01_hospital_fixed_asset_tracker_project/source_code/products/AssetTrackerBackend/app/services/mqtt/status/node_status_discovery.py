"""
File: node_status_discovery.py
Author: Farros Ramzy (you@domain.com)
Description: Auto-discovers unknown nodes from MQTT status messages.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from app.db.node_db_model import Node


def build_discovered_node(
    status_payload: dict, mqtt_broker: str, mqtt_port: int
) -> Node:
    """_summary_ :\n
    Unknown node: DISCOVERED, but not ONLINE yet.
    Args:
        status_payload (dict): _description_
        mqtt_broker (str): _description_
        mqtt_port (int): _description_

    Returns:
        Node: _description_
    """
    return Node(
        device_id=status_payload["device_id"],
        alias="",
        role="",
        hospital_id=status_payload["hospital_id"],
        hospital_name=status_payload["hospital_name"],
        room_name=status_payload["room_name"],
        mqtt_host=mqtt_broker,
        mqtt_port=mqtt_port,
        is_provisioned=False,
        status="DISCOVERED",
        last_ping_at=None,
        last_event_at=status_payload["timestamp"],
        last_message="auto-discovered from MQTT status",
    )
