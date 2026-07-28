"""
File: settings.py
Author: Farros Ramzy (you@domain.com)
Description: Admin-only system settings routes.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from fastapi import APIRouter, Depends

from app.db_models import User
from app.models import MqttSettingsRequest
from app.services.authority.auth_dependencies import require_role
from app.services.mqtt.mqtt_client import (
    get_safe_mqtt_settings,
    reset_mqtt_settings,
    restart_mqtt_background_worker,
    save_mqtt_settings,
)

router = APIRouter(prefix="/settings", tags=["settings"])


@router.get("/mqtt")
def get_mqtt_settings(
    current_user: User = Depends(require_role("admin", "test_user", "technician")),
):
    return {"settings": get_safe_mqtt_settings()}


@router.put("/mqtt")
def update_mqtt_settings(
    req: MqttSettingsRequest,
    current_user: User = Depends(require_role("admin", "test_user")),
):
    result = save_mqtt_settings(
        request=req,
        updated_by_user_id=current_user.id,
    )
    restart_mqtt_background_worker()
    return result


@router.post("/mqtt/reconnect")
def reconnect_mqtt(
    current_user: User = Depends(require_role("admin", "test_user")),
):
    restart_mqtt_background_worker()

    return {
        "message": "mqtt_reconnect_requested",
        "settings": get_safe_mqtt_settings(),
    }


@router.post("/mqtt/reset-default")
def reset_mqtt_to_default(
    current_user: User = Depends(require_role("admin", "test_user")),
):
    result = reset_mqtt_settings()
    restart_mqtt_background_worker()
    return result
