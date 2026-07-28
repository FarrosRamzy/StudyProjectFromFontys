"""
File: test_mqtt_topics.py
Author: Farros Ramzy (you@domain.com)
Description: Unit tests for parsing supported MQTT topic structures and rejecting invalid topics.
Version: 0.1
Date: 2026-05-29

Copyright (c) 2026
"""

from app.services.mqtt.mqtt_topics import (
    get_mqtt_subscribe_topics,
    parse_mqtt_topic,
)
from app.services.mqtt.settings.mqtt_settings_factory import get_default_mqtt_settings


def topic(path: str) -> str:
    return f"{get_default_mqtt_settings().topic_namespace}/{path}"


def expected(device_id: str, category: str, event: str = "") -> dict:
    return {
        "hospital_id": get_default_mqtt_settings().hospital_id,
        "device_id": device_id,
        "category": category,
        "event": event,
    }


def test_subscribe_topics_use_active_namespace():
    settings = get_default_mqtt_settings()
    topics = get_mqtt_subscribe_topics(settings)

    assert all(item.startswith(settings.topic_namespace) for item in topics)
    assert all("hospital/+" not in item for item in topics)


def test_parse_rfid_detected_topic():
    result = parse_mqtt_topic(topic("nodes/NODE_1/rfid/detected"))

    assert result == expected("NODE_1", "rfid", "detected")


def test_parse_rfid_registration_topic():
    result = parse_mqtt_topic(topic("nodes/REG_NODE/rfid/asset-registration"))

    assert result == expected("REG_NODE", "rfid", "asset-registration")


def test_parse_heartbeat_topic():
    result = parse_mqtt_topic(topic("nodes/NODE_1/heartbeat"))

    assert result == expected("NODE_1", "heartbeat")


def test_parse_status_topic():
    result = parse_mqtt_topic(topic("nodes/NODE_1/status"))

    assert result == expected("NODE_1", "status")


def test_parse_command_ack_topic():
    result = parse_mqtt_topic(topic("nodes/NODE_1/commands/ack"))

    assert result == expected("NODE_1", "commands", "ack")


def test_rejects_other_hospital_namespace():
    assert parse_mqtt_topic("hospital/HOSP_2/nodes/NODE_1/status") is None


def test_invalid_short_topic_returns_none():
    assert parse_mqtt_topic("invalid/topic") is None


def test_invalid_middle_section_returns_none():
    assert parse_mqtt_topic(topic("devices/NODE_1/heartbeat")) is None
