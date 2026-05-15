"""
File: mqtt_client.py
Author: Farros Ramzy (you@domain.com)
Description: Description
Version: 0.1
Date: 2026-04-23

Copyright (c) 2026
"""

from __future__ import annotations

import os
from pathlib import Path
from dotenv import load_dotenv

import json
import threading
from typing import Any
import paho.mqtt.client as my_mqtt

from app.services.mqtt.mqtt_detection_handler import handle_detection
from app.services.mqtt.mqtt_node_status_handler import handle_node_status
from app.services.mqtt.mqtt_registration_handler import handle_registration_scan

BASE_DIR = Path(__file__).resolve().parents[3]
load_dotenv(BASE_DIR / ".env")

MQTT_BROKER = os.getenv("MQTT_BROKER", "localhost")
MQTT_PORT = int(os.getenv("MQTT_PORT", "1883"))

MQTT_USERNAME = os.getenv("MQTT_USERNAME", "")
MQTT_PASSWORD = os.getenv("MQTT_PASSWORD", "")
MQTT_TLS_ENABLED = os.getenv("MQTT_TLS_ENABLED", "false").lower() == "true"

TOPIC_RFID_DETECTION = "hospital/+/nodes/+/rfid/detected"
TOPIC_RFID_REGISTRATION = "hospital/+/nodes/+/rfid/asset-registration"
TOPIC_HEARTBEAT = "hospital/+/nodes/+/heartbeat"
TOPIC_STATUS = "hospital/+/nodes/+/status"

_worker_started = False
_worker_lock = threading.Lock()


def on_connect(
    client: my_mqtt.Client,
    user_data: Any,
    flags: dict[str, Any],
    reason_code: Any,
    properties: Any = None,
) -> None:
    print(f"[MQTT] Connected with reason code: {reason_code}")

    client.subscribe(TOPIC_RFID_REGISTRATION)
    client.subscribe(TOPIC_RFID_DETECTION)
    client.subscribe(TOPIC_HEARTBEAT)
    client.subscribe(TOPIC_STATUS)


def parse_mqtt_topic(topic: str) -> dict[str, str] | None:
    parts = topic.split("/")

    if len(parts) < 5:
        return None

    if parts[0] != "hospital" or parts[2] != "nodes":
        return None

    hospital_id = parts[1]
    device_id = parts[3]

    if len(parts) == 6 and parts[4] == "rfid":
        return {
            "hospital_id": hospital_id,
            "device_id": device_id,
            "category": "rfid",
            "event": parts[5],
        }

    if len(parts) == 5 and parts[4] in {"heartbeat", "status"}:
        return {
            "hospital_id": hospital_id,
            "device_id": device_id,
            "category": parts[4],
            "event": "",
        }

    return None


def on_message(
    client: my_mqtt.Client, user_data: Any, msg: my_mqtt.MQTTMessage
) -> None:
    topic_info = parse_mqtt_topic(msg.topic)

    if topic_info is None:
        print(f"[MQTT] Ignored invalid topic: {msg.topic}")
        return

    try:
        payload = json.loads(msg.payload.decode("utf-8"))
    except Exception as exc:
        print(f"[MQTT] Invalid JSON payload: {exc}")
        return

    if not isinstance(payload, dict):
        print(f"[MQTT] Ignored non-object JSON payload on topic: {msg.topic}")
        return

    payload_device_id = payload.get("device_id", "")
    payload_hospital_id = payload.get("hospital_id", "")

    if payload_device_id and payload_device_id != topic_info["device_id"]:
        print("[MQTT] Device ID mismatch between topic and payload")
        return

    if payload_hospital_id and payload_hospital_id != topic_info["hospital_id"]:
        print("[MQTT] Hospital ID mismatch between topic and payload")
        return

    payload["device_id"] = topic_info["device_id"]
    payload["hospital_id"] = topic_info["hospital_id"]

    print("[MQTT] Topic:", msg.topic)
    print("[MQTT] Parsed:", topic_info)
    print("[MQTT] Payload:", payload)

    try:
        if topic_info["category"] == "rfid" and topic_info["event"] == "detected":
            handle_detection(payload)
            return

        if (
            topic_info["category"] == "rfid"
            and topic_info["event"] == "asset-registration"
        ):
            handle_registration_scan(payload)
            return

        if topic_info["category"] in {"heartbeat", "status"}:
            handle_node_status(payload, MQTT_BROKER, MQTT_PORT)
            return

        print(f"[MQTT] Unhandled topic: {msg.topic}")

    except Exception as exc:
        print(f"[MQTT] Handler error for topic {msg.topic}: {exc}")


def mqtt_worker() -> None:
    """Start blocking MQTT loop in a background thread."""
    client = my_mqtt.Client(my_mqtt.CallbackAPIVersion.VERSION2)
    client.on_connect = on_connect
    client.on_message = on_message

    if MQTT_USERNAME and MQTT_PASSWORD:
        client.username_pw_set(MQTT_USERNAME, MQTT_PASSWORD)

    if MQTT_TLS_ENABLED:
        client.tls_set()

    print(f"[MQTT] Connecting to broker {MQTT_BROKER}:{MQTT_PORT} ...")
    print(
        "[MQTT CONFIG]",
        {
            "broker": MQTT_BROKER,
            "port": MQTT_PORT,
            "username_set": bool(MQTT_USERNAME),
            "password_set": bool(MQTT_PASSWORD),
            "tls": MQTT_TLS_ENABLED,
        },
    )
    try:
        client.connect(MQTT_BROKER, MQTT_PORT, keepalive=60)
        client.loop_forever()
    except Exception as exc:
        print(f"[MQTT] Worker stopped: {exc}")


def start_mqtt_background_worker() -> None:
    """Start MQTT worker in a daemon thread."""
    global _worker_started
    with _worker_lock:
        if _worker_started:
            print("[MQTT] Worker already started.Skipping duplicate startup.")
            return

        thread = threading.Thread(target=mqtt_worker, daemon=True, name="mqtt-worker")
        thread.start()
        _worker_started = True
