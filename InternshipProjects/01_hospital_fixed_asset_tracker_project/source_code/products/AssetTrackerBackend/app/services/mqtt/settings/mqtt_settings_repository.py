"""
File: mqtt_settings_repository.py
Author: Farros Ramzy (you@domain.com)
Description: Database repository for MQTT settings.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from app.db.system_setting_db_model import SystemSetting

SETTING_PREFIX = "mqtt."


def get_mqtt_setting_values(db) -> dict[str, str]:
    return {
        row.key: row.value
        for row in db.query(SystemSetting)
        .filter(SystemSetting.key.like(f"{SETTING_PREFIX}%"))
        .all()
    }


def save_mqtt_setting_values(db, values: dict[str, str]) -> None:
    for key, value in values.items():
        upsert_setting(db, key, value)


def delete_mqtt_settings(db) -> None:
    db.query(SystemSetting).filter(SystemSetting.key.like(f"{SETTING_PREFIX}%")).delete(
        synchronize_session=False
    )


def upsert_setting(db, key: str, value: str) -> None:
    setting = db.query(SystemSetting).filter(SystemSetting.key == key).first()

    if setting is None:
        db.add(SystemSetting(key=key, value=value))
        return

    setting.value = value
