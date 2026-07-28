"""
File: setup_flag_service.py
Author: Farros Ramzy (you@domain.com)
Description: Persistent first-admin setup completion flag helpers.
Version: 0.1
Date: 2026-06-05

Copyright (c) 2026
"""

from app.db_models import SystemSetting

FIRST_ADMIN_SETUP_KEY = "first_admin_setup_completed"
TRUE_VALUE = "true"


def get_setting(db, key: str):
    return db.query(SystemSetting).filter(SystemSetting.key == key).first()


def is_first_admin_setup_completed(db) -> bool:
    setting = get_setting(db, FIRST_ADMIN_SETUP_KEY)
    return setting is not None and setting.value == TRUE_VALUE


def mark_first_admin_setup_completed(db) -> None:
    setting = get_setting(db, FIRST_ADMIN_SETUP_KEY)

    if setting is None:
        setting = SystemSetting(
            key=FIRST_ADMIN_SETUP_KEY,
            value=TRUE_VALUE,
        )
    else:
        setting.value = TRUE_VALUE

    db.add(setting)
