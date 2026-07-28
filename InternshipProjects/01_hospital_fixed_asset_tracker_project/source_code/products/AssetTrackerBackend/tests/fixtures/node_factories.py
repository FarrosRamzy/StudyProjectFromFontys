"""
File: node_factories.py
Author: Farros Ramzy (you@domain.com)
Description: Node factory fixtures.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

import pytest

from app.db_models import Node
from app.utils import now_wib


@pytest.fixture()
def make_node(db_session):
    def _make_node(
        device_id="NODE_1",
        alias=None,
        role="CHECKPOINT",
        hospital_id="HOSP_1",
        hospital_name="General Hospital",
        room_name="ICU",
        mqtt_host="localhost",
        mqtt_port=1883,
        status="ONLINE",
        is_provisioned=True,
        last_ping_at=None,
        last_event_at=None,
        last_message="test node",
    ):
        node = Node(
            device_id=device_id,
            alias=alias or device_id,
            role=role,
            hospital_id=hospital_id,
            hospital_name=hospital_name,
            room_name=room_name,
            mqtt_host=mqtt_host,
            mqtt_port=mqtt_port,
            is_provisioned=is_provisioned,
            status=status,
            last_ping_at=last_ping_at,
            last_event_at=last_event_at or now_wib(),
            last_message=last_message,
        )

        db_session.add(node)
        db_session.commit()
        db_session.refresh(node)

        return node

    return _make_node
