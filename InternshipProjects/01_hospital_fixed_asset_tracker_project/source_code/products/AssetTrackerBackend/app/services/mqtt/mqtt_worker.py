"""
File: mqtt_worker.py
Author: Farros Ramzy (you@domain.com)
Description: MQTT background worker lifecycle.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from __future__ import annotations

import threading

import paho.mqtt.client as my_mqtt

from app.services.mqtt.mqtt_router import on_connect, on_message
from app.services.mqtt.settings.mqtt_settings_service import get_active_mqtt_settings

_worker_started = False
_worker_lock = threading.Lock()
_mqtt_client: my_mqtt.Client | None = None
_mqtt_client_lock = threading.Lock()


def get_mqtt_client() -> my_mqtt.Client | None:
    with _mqtt_client_lock:
        return _mqtt_client


def set_mqtt_client(client: my_mqtt.Client | None) -> None:
    global _mqtt_client

    with _mqtt_client_lock:
        _mqtt_client = client


def mqtt_worker() -> None:
    global _worker_started

    settings = get_active_mqtt_settings()

    if not settings.enabled:
        print("[MQTT] MQTT is disabled in system settings.")
        mark_worker_stopped()
        return

    client = build_mqtt_client(settings)
    set_mqtt_client(client)

    try:
        connect_and_loop(client, settings)

    except Exception as exc:
        print(f"[MQTT] Worker stopped: {exc}")

    finally:
        if get_mqtt_client() is client:
            set_mqtt_client(None)
        mark_worker_stopped()


def build_mqtt_client(settings) -> my_mqtt.Client:
    client = my_mqtt.Client(
        callback_api_version=my_mqtt.CallbackAPIVersion.VERSION2,
        client_id=settings.client_id,
    )
    client.user_data_set({"settings": settings})
    client.on_connect = on_connect
    client.on_message = on_message

    if settings.username:
        client.username_pw_set(settings.username, settings.password or None)

    if settings.tls_enabled:
        client.tls_set()

    return client


def connect_and_loop(client: my_mqtt.Client, settings) -> None:
    print_mqtt_config(settings)
    client.connect(settings.broker_host, settings.broker_port, keepalive=60)
    client.loop_forever()


def print_mqtt_config(settings) -> None:
    print(
        "[MQTT CONFIG]",
        {
            "broker": settings.broker_host,
            "port": settings.broker_port,
            "client_id": settings.client_id,
            "username_set": bool(settings.username),
            "password_set": bool(settings.password),
            "tls": settings.tls_enabled,
            "namespace": settings.topic_namespace,
        },
    )


def start_mqtt_background_worker() -> None:
    global _worker_started

    with _worker_lock:
        if _worker_started:
            print("[MQTT] Worker already started. Skipping duplicate startup.")
            return

        _worker_started = True

    threading.Thread(target=mqtt_worker, daemon=True, name="mqtt-worker").start()


def restart_mqtt_background_worker() -> None:
    client = get_mqtt_client()

    if client is not None:
        try:
            client.disconnect()
        except Exception as exc:
            print(f"[MQTT] Failed to disconnect old client: {exc}")

    mark_worker_stopped()
    start_mqtt_background_worker()


def mark_worker_stopped() -> None:
    global _worker_started

    with _worker_lock:
        _worker_started = False
