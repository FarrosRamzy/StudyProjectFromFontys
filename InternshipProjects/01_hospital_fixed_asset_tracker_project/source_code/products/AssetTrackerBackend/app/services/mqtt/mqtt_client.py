"""
File: mqtt_client.py
Author: Farros Ramzy (you@domain.com)
Description:  Compatibility facade for MQTT services.
                Old imports can still use:
                from app.services.mqtt.mqtt_client import start_mqtt_background_worker
Version: 0.1
Date: 2026-04-23

Copyright (c) 2026
"""

from app.services.mqtt.mqtt_config import (
    MQTT_BROKER,
    MQTT_PASSWORD,
    MQTT_PORT,
    MQTT_TLS_ENABLED,
    MQTT_USERNAME,
)
from app.services.mqtt.mqtt_publisher import publish_node_blink_command
from app.services.mqtt.mqtt_router import on_connect, on_message
from app.services.mqtt.settings.mqtt_settings_service import (
    get_active_mqtt_settings,
    get_safe_mqtt_settings,
    reset_mqtt_settings,
    save_mqtt_settings,
)
from app.services.mqtt.mqtt_topics import (
    TOPIC_COMMAND_ACK,
    TOPIC_HEARTBEAT,
    TOPIC_RFID_DETECTION,
    TOPIC_RFID_REGISTRATION,
    TOPIC_STATUS,
    build_node_command_topic,
    get_mqtt_subscribe_topics,
    parse_mqtt_topic,
)
from app.services.mqtt.mqtt_worker import (
    get_mqtt_client,
    mqtt_worker,
    restart_mqtt_background_worker,
    start_mqtt_background_worker,
)

__all__ = [
    "MQTT_BROKER",
    "MQTT_PASSWORD",
    "MQTT_PORT",
    "MQTT_TLS_ENABLED",
    "MQTT_USERNAME",
    "TOPIC_COMMAND_ACK",
    "TOPIC_HEARTBEAT",
    "TOPIC_RFID_DETECTION",
    "TOPIC_RFID_REGISTRATION",
    "TOPIC_STATUS",
    "build_node_command_topic",
    "get_active_mqtt_settings",
    "get_mqtt_client",
    "get_mqtt_subscribe_topics",
    "get_safe_mqtt_settings",
    "mqtt_worker",
    "on_connect",
    "on_message",
    "parse_mqtt_topic",
    "publish_node_blink_command",
    "reset_mqtt_settings",
    "restart_mqtt_background_worker",
    "save_mqtt_settings",
    "start_mqtt_background_worker",
]
