"""
File: mqtt_settings_service.py
Author: Farros Ramzy (you@domain.com)
Description: Database-backed runtime MQTT settings service.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from app.database import SessionLocal
from app.services.mqtt.settings.mqtt_settings_factory import build_mqtt_settings
from app.services.mqtt.settings.mqtt_settings_repository import (
    delete_mqtt_settings,
    get_mqtt_setting_values,
    save_mqtt_setting_values,
)
from app.services.mqtt.settings.mqtt_settings_validation import (
    normalize_topic_namespace,
    validate_broker_host,
    validate_broker_port,
)


def get_active_mqtt_settings():
    db = SessionLocal()

    try:
        return build_mqtt_settings(get_mqtt_setting_values(db))

    finally:
        db.close()


def get_safe_mqtt_settings() -> dict:
    return get_active_mqtt_settings().to_safe_dict()


def save_mqtt_settings(request, updated_by_user_id: int | None = None) -> dict:
    db = SessionLocal()

    try:
        current = get_mqtt_setting_values(db)
        values = build_mqtt_setting_values(request, current, updated_by_user_id)
        save_mqtt_setting_values(db, values)
        db.commit()

    except Exception:
        db.rollback()
        raise

    finally:
        db.close()

    return {
        "message": "mqtt_settings_saved",
        "settings": get_safe_mqtt_settings(),
    }


def reset_mqtt_settings() -> dict:
    db = SessionLocal()

    try:
        delete_mqtt_settings(db)
        db.commit()

    except Exception:
        db.rollback()
        raise

    finally:
        db.close()

    return {
        "message": "mqtt_settings_reset_to_default",
        "settings": get_safe_mqtt_settings(),
    }


def build_mqtt_setting_values(request, current: dict, user_id: int | None) -> dict:
    broker_port = validate_broker_port(request.broker_port)
    topic_namespace = normalize_topic_namespace(request.topic_namespace)
    password = request.password or current.get("mqtt.password", "")

    values = {
        "mqtt.broker_host": validate_broker_host(request.broker_host),
        "mqtt.broker_port": str(broker_port),
        "mqtt.hospital_name": str(request.hospital_name or "").strip(),
        "mqtt.tls_enabled": str(bool(request.tls_enabled)).lower(),
        "mqtt.username": str(request.username or "").strip(),
        "mqtt.password": password,
        "mqtt.topic_namespace": topic_namespace,
        "mqtt.client_id": str(request.client_id or "").strip(),
        "mqtt.enabled": str(bool(request.enabled)).lower(),
    }

    if user_id is not None:
        values["mqtt.updated_by_user_id"] = str(user_id)

    return values
