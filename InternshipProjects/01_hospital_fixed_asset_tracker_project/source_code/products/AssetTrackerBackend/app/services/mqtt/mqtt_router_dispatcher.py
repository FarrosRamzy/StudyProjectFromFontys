"""
File: mqtt_router_dispatcher.py
Author: Farros Ramzy (you@domain.com)
Description: Dispatches parsed MQTT messages to domain handlers.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from app.services.mqtt.mqtt_detection_handler import handle_detection
from app.services.mqtt.mqtt_node_status_handler import handle_node_status
from app.services.mqtt.mqtt_registration_handler import handle_registration_scan
from app.services.realtime.broadcast_service import schedule_broadcast


def dispatch_mqtt_message(topic_info: dict, payload: dict, settings) -> None:
    category = topic_info["category"]
    event = topic_info["event"]

    if category == "rfid" and event == "detected":
        handle_detection(payload)
        return

    if category == "rfid" and event == "asset-registration":
        handle_registration_scan(payload)
        return

    if category in {"heartbeat", "status"}:
        handle_node_status(payload, settings.broker_host, settings.broker_port)
        return

    if category == "commands" and event == "ack":
        broadcast_command_ack(topic_info, payload)
        return

    print(f"[MQTT] Unhandled topic category: {topic_info}")


def broadcast_command_ack(topic_info: dict, payload: dict) -> None:
    schedule_broadcast(
        {
            "type": "node_identify_ack",
            "device_id": topic_info["device_id"],
            "hospital_id": topic_info["hospital_id"],
            "payload": payload,
        }
    )
