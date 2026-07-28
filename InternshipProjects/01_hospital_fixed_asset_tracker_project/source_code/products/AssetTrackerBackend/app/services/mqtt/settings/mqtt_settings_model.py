"""
File: mqtt_settings_model.py
Author: Farros Ramzy (you@domain.com)
Description: Small value object for runtime MQTT settings.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from dataclasses import dataclass


@dataclass(frozen=True)
class MqttSettings:
    broker_host: str
    broker_port: int
    hospital_name: str
    tls_enabled: bool
    username: str
    password: str
    topic_namespace: str
    client_id: str
    enabled: bool

    @property
    def hospital_id(self) -> str:
        return self.topic_namespace.split("/")[1]

    def to_safe_dict(self) -> dict:
        return {
            "broker_host": self.broker_host,
            "broker_port": self.broker_port,
            "hospital_name": self.hospital_name,
            "tls_enabled": self.tls_enabled,
            "username": self.username,
            "password_set": bool(self.password),
            "topic_namespace": self.topic_namespace,
            "hospital_id": self.hospital_id,
            "client_id": self.client_id,
            "enabled": self.enabled,
        }
