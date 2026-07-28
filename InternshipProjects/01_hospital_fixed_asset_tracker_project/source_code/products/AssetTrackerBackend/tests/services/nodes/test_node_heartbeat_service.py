"""
File: test_node_heartbeat_service.py
Author: Farros Ramzy (you@domain.com)
Description: Node status service heartbeat tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from datetime import timedelta

from app.services.mqtt.mqtt_node_status_handler import handle_node_status
from app.services.nodes.node_status_monitor import check_offline_nodes
from app.utils import now_wib


def test_heartbeat_from_known_provisioned_node_sets_node_online(
    db_session,
    make_node,
):
    node = make_node(
        device_id="NODE_HEARTBEAT_1",
        role="CHECKPOINT",
        room_name="ICU",
        hospital_id="HOSP_1",
        is_provisioned=True,
        status="ASSIGNED",
        last_ping_at=None,
    )

    payload = {
        "device_id": "NODE_HEARTBEAT_1",
        "hospital_id": "HOSP_1",
        "hospital_name": "General Hospital",
        "room_name": "ICU",
        "status": "OK",
        "message": "heartbeat",
        "timestamp": now_wib().isoformat(),
    }

    handle_node_status(payload, mqtt_broker="localhost", mqtt_port=1883)

    db_session.refresh(node)

    assert node.status == "ONLINE"
    assert node.last_ping_at is not None
    assert node.last_message == "heartbeat"

def test_goodbye_status_sets_node_offline(db_session, make_node):
    node = make_node(
        device_id="NODE_HEARTBEAT_2",
        role="CHECKPOINT",
        room_name="ICU",
        hospital_id="HOSP_1",
        is_provisioned=True,
        status="ONLINE",
    )

    payload = {
        "device_id": "NODE_HEARTBEAT_2",
        "hospital_id": "HOSP_1",
        "status": "GOODBYE",
        "message": "node shutting down",
        "timestamp": now_wib().isoformat(),
    }

    handle_node_status(payload, mqtt_broker="localhost", mqtt_port=1883)

    db_session.refresh(node)

    assert node.status == "OFFLINE"
    assert node.last_message == "node shutting down"

def test_heartbeat_from_unknown_node_auto_discovers_node(db_session):
    payload = {
        "device_id": "NODE_UNKNOWN_HEARTBEAT",
        "hospital_id": "HOSP_1",
        "hospital_name": "General Hospital",
        "room_name": "ICU",
        "status": "OK",
        "message": "heartbeat",
        "timestamp": now_wib().isoformat(),
    }

    handle_node_status(payload, mqtt_broker="localhost", mqtt_port=1883)

    from app.db_models import Node

    node = (
        db_session.query(Node)
        .filter(Node.device_id == "NODE_UNKNOWN_HEARTBEAT")
        .first()
    )

    assert node is not None
    assert node.status == "DISCOVERED"
    assert node.is_provisioned is False

def test_heartbeat_from_disabled_node_is_ignored(db_session, make_node):
    node = make_node(
        device_id="NODE_DISABLED_HEARTBEAT",
        role="CHECKPOINT",
        room_name="ICU",
        hospital_id="HOSP_1",
        is_provisioned=True,
        status="DISABLED",
    )

    payload = {
        "device_id": "NODE_DISABLED_HEARTBEAT",
        "hospital_id": "HOSP_1",
        "status": "OK",
        "message": "heartbeat",
        "timestamp": now_wib().isoformat(),
    }

    handle_node_status(payload, mqtt_broker="localhost", mqtt_port=1883)

    db_session.refresh(node)

    assert node.status == "DISABLED"
