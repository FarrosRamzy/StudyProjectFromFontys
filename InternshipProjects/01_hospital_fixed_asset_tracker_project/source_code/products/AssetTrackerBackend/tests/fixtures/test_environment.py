"""
File: test_environment.py
Author: Farros Ramzy (you@domain.com)
Description: Test environment variables for backend test imports.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

import os


def configure_test_environment() -> None:
    os.environ.setdefault("DATABASE_URL", "sqlite:///./test_asset_tracker.db")
    os.environ.setdefault("JWT_SECRET_KEY", "test-secret")
    os.environ.setdefault("NODE_PROVISIONING_KEY", "test-node-key")
    os.environ.setdefault("MQTT_BROKER", "localhost")
    os.environ.setdefault("MQTT_PORT", "1883")
    os.environ.setdefault("MQTT_USERNAME", "")
    os.environ.setdefault("MQTT_PASSWORD", "")
    os.environ.setdefault("MQTT_TLS_ENABLED", "false")


configure_test_environment()
