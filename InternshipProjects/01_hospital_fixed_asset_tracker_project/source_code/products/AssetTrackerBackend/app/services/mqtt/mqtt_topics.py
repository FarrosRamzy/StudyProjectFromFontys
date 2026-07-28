"""
File: mqtt_topics.py
Author: Farros Ramzy (you@domain.com)
Description: MQTT topic builders and parser for one active hospital namespace.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from app.services.mqtt.settings.mqtt_settings_factory import get_default_mqtt_settings


def build_mqtt_topic(*parts: str) -> str:
    clean_parts = [str(part).strip("/") for part in parts if str(part or "").strip("/")]

    return "/".join(clean_parts)


def get_mqtt_subscribe_topics(settings) -> list[str]:
    namespace = settings.topic_namespace

    return [
        build_mqtt_topic(namespace, "nodes", "+", "rfid", "asset-registration"),
        build_mqtt_topic(namespace, "nodes", "+", "rfid", "detected"),
        build_mqtt_topic(namespace, "nodes", "+", "heartbeat"),
        build_mqtt_topic(namespace, "nodes", "+", "status"),
        build_mqtt_topic(namespace, "nodes", "+", "commands", "ack"),
    ]


def build_node_command_topic(settings, device_id: str, command_name: str) -> str:
    return build_mqtt_topic(
        settings.topic_namespace,
        "nodes",
        device_id,
        "commands",
        command_name,
    )


def parse_mqtt_topic(topic: str, settings=None) -> dict[str, str] | None:
    settings = settings or get_default_mqtt_settings()
    topic_parts = split_topic(topic)
    namespace_parts = split_topic(settings.topic_namespace)

    if topic_parts[: len(namespace_parts)] != namespace_parts:
        return None

    remaining_parts = topic_parts[len(namespace_parts) :]

    if len(remaining_parts) < 3 or remaining_parts[0] != "nodes":
        return None

    return parse_node_topic(remaining_parts, settings.hospital_id)


def parse_node_topic(parts: list[str], hospital_id: str) -> dict[str, str] | None:
    device_id = parts[1]

    if len(parts) == 4 and parts[2] == "rfid":
        return make_topic_info(hospital_id, device_id, "rfid", parts[3])

    if len(parts) == 3 and parts[2] in {"heartbeat", "status"}:
        return make_topic_info(hospital_id, device_id, parts[2], "")

    if len(parts) == 4 and parts[2] == "commands":
        return make_topic_info(hospital_id, device_id, "commands", parts[3])

    return None


def make_topic_info(
    hospital_id: str,
    device_id: str,
    category: str,
    event: str,
) -> dict[str, str]:
    return {
        "hospital_id": hospital_id,
        "device_id": device_id,
        "category": category,
        "event": event,
    }


def split_topic(topic: str) -> list[str]:
    return [part for part in str(topic or "").strip("/").split("/") if part]


_default_topics = get_mqtt_subscribe_topics(get_default_mqtt_settings())
TOPIC_RFID_REGISTRATION = _default_topics[0]
TOPIC_RFID_DETECTION = _default_topics[1]
TOPIC_HEARTBEAT = _default_topics[2]
TOPIC_STATUS = _default_topics[3]
TOPIC_COMMAND_ACK = _default_topics[4]
