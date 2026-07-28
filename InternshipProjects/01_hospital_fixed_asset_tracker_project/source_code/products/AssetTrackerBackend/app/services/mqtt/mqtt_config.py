"""
File: mqtt_config.py
Author: Farros Ramzy (you@domain.com)
Description: MQTT configuration loaded from .env.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

import os
from pathlib import Path

from dotenv import load_dotenv

BASE_DIR = Path(__file__).resolve().parents[3]
load_dotenv(BASE_DIR / ".env")


def get_bool_env(name: str, default: str = "false") -> bool:
    return os.getenv(name, default).strip().lower() in {
        "true",
        "1",
        "yes",
        "on",
    }


DEFAULT_MQTT_BROKER = os.getenv(
    "DEFAULT_MQTT_BROKER", os.getenv("MQTT_BROKER", "localhost")
).strip()
DEFAULT_MQTT_PORT = int(os.getenv("DEFAULT_MQTT_PORT", os.getenv("MQTT_PORT", "1883")))
DEFAULT_MQTT_USERNAME = os.getenv(
    "DEFAULT_MQTT_USERNAME", os.getenv("MQTT_USERNAME", "")
).strip()
DEFAULT_MQTT_PASSWORD = os.getenv(
    "DEFAULT_MQTT_PASSWORD", os.getenv("MQTT_PASSWORD", "")
)
DEFAULT_MQTT_TLS_ENABLED = get_bool_env(
    "DEFAULT_MQTT_TLS_ENABLED", os.getenv("MQTT_TLS_ENABLED", "false")
)
DEFAULT_MQTT_TOPIC_NAMESPACE = os.getenv(
    "DEFAULT_MQTT_TOPIC_NAMESPACE",
    os.getenv("MQTT_TOPIC_NAMESPACE", "hospital/default-hospital"),
).strip()
DEFAULT_MQTT_CLIENT_ID = os.getenv(
    "DEFAULT_MQTT_CLIENT_ID",
    os.getenv("MQTT_CLIENT_ID", "asset-tracker-backend-default"),
).strip()
DEFAULT_MQTT_ENABLED = get_bool_env("DEFAULT_MQTT_ENABLED", "true")

MQTT_BROKER = DEFAULT_MQTT_BROKER
MQTT_PORT = DEFAULT_MQTT_PORT
MQTT_USERNAME = DEFAULT_MQTT_USERNAME
MQTT_PASSWORD = DEFAULT_MQTT_PASSWORD
MQTT_TLS_ENABLED = DEFAULT_MQTT_TLS_ENABLED
