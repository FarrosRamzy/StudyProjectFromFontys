"""
File: test_node_offline_monitor_service.py
Author: Farros Ramzy (you@domain.com)
Description: Node offline status monitor service tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from datetime import timedelta

from app.services.mqtt.mqtt_node_status_handler import handle_node_status
from app.services.nodes.node_status_monitor import check_offline_nodes
from app.utils import now_wib


def test_check_offline_nodes_marks_old_online_node_offline(
    db_session,
    make_node,
):
    old_time = now_wib() - timedelta(minutes=5)

    node = make_node(
        device_id="NODE_TIMEOUT",
        role="CHECKPOINT",
        room_name="ICU",
        hospital_id="HOSP_1",
        is_provisioned=True,
        status="ONLINE",
        last_ping_at=old_time,
        last_event_at=old_time,
    )

    check_offline_nodes()

    db_session.refresh(node)

    assert node.status == "OFFLINE"
    assert node.last_message == "heartbeat timeout"

def test_check_offline_nodes_does_not_mark_disabled_node_offline(
    db_session,
    make_node,
):
    old_time = now_wib() - timedelta(minutes=5)

    node = make_node(
        device_id="NODE_DISABLED_TIMEOUT",
        role="CHECKPOINT",
        room_name="ICU",
        hospital_id="HOSP_1",
        is_provisioned=True,
        status="DISABLED",
        last_ping_at=old_time,
        last_event_at=old_time,
    )

    check_offline_nodes()

    db_session.refresh(node)

    assert node.status == "DISABLED"

def test_check_offline_nodes_keeps_recent_node_online(
    db_session,
    make_node,
):
    recent_time = now_wib()

    node = make_node(
        device_id="NODE_RECENT",
        role="CHECKPOINT",
        room_name="ICU",
        hospital_id="HOSP_1",
        is_provisioned=True,
        status="ONLINE",
        last_ping_at=recent_time,
        last_event_at=recent_time,
    )

    check_offline_nodes()

    db_session.refresh(node)

    assert node.status == "ONLINE"
