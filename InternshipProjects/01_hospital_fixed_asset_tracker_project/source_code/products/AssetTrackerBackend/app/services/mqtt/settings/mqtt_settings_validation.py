"""
File: mqtt_settings_validation.py
Author: Farros Ramzy (you@domain.com)
Description: Validation helpers for MQTT settings.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from fastapi import HTTPException, status


def normalize_topic_namespace(value: str) -> str:
    namespace = str(value or "").strip().strip("/")

    if not namespace:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="mqtt_topic_namespace_required",
        )

    if "+" in namespace or "#" in namespace:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="mqtt_topic_namespace_must_not_use_wildcards",
        )

    parts = [part.strip() for part in namespace.split("/") if part.strip()]

    if len(parts) != 2 or parts[0] != "hospital":
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="mqtt_topic_namespace_format_must_be_hospital_id",
        )

    return "/".join(parts)


def parse_bool(value) -> bool:
    return str(value or "").strip().lower() in {
        "true",
        "1",
        "yes",
        "on",
    }


def validate_broker_host(value: str) -> str:
    broker_host = str(value or "").strip()

    if not broker_host:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="mqtt_broker_host_required",
        )

    return broker_host


def validate_broker_port(value: int) -> int:
    broker_port = int(value)

    if broker_port < 1 or broker_port > 65535:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="mqtt_port_must_be_1_to_65535",
        )

    return broker_port
