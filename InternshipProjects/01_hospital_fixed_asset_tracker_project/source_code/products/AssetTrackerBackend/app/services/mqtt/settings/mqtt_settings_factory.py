"""
File: mqtt_settings_factory.py
Author: Farros Ramzy (you@domain.com)
Description: Builds MQTT settings from environment/database values.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from app.services.mqtt.mqtt_config import (
    DEFAULT_MQTT_BROKER,
    DEFAULT_MQTT_CLIENT_ID,
    DEFAULT_MQTT_ENABLED,
    DEFAULT_MQTT_PASSWORD,
    DEFAULT_MQTT_PORT,
    DEFAULT_MQTT_TLS_ENABLED,
    DEFAULT_MQTT_TOPIC_NAMESPACE,
    DEFAULT_MQTT_USERNAME,
)
from app.services.mqtt.settings.mqtt_settings_model import MqttSettings
from app.services.mqtt.settings.mqtt_settings_validation import (
    normalize_topic_namespace,
    parse_bool,
)


def build_mqtt_settings(values: dict[str, str] | None = None) -> MqttSettings:
    values = values or {}
    topic_namespace = normalize_topic_namespace(
        values.get("mqtt.topic_namespace", DEFAULT_MQTT_TOPIC_NAMESPACE)
    )
    hospital_id = topic_namespace.split("/")[1]

    return MqttSettings(
        broker_host=values.get("mqtt.broker_host", DEFAULT_MQTT_BROKER),
        broker_port=int(values.get("mqtt.broker_port", DEFAULT_MQTT_PORT)),
        hospital_name=values.get(
            "mqtt.hospital_name",
            title_case_hospital_id(hospital_id),
        ),
        tls_enabled=parse_bool(
            values.get("mqtt.tls_enabled", str(DEFAULT_MQTT_TLS_ENABLED))
        ),
        username=values.get("mqtt.username", DEFAULT_MQTT_USERNAME),
        password=values.get("mqtt.password", DEFAULT_MQTT_PASSWORD),
        topic_namespace=topic_namespace,
        client_id=values.get("mqtt.client_id", DEFAULT_MQTT_CLIENT_ID),
        enabled=parse_bool(values.get("mqtt.enabled", str(DEFAULT_MQTT_ENABLED))),
    )


def get_default_mqtt_settings() -> MqttSettings:
    return build_mqtt_settings({})


def title_case_hospital_id(hospital_id: str) -> str:
    return str(hospital_id or "").replace("-", " ").title()
