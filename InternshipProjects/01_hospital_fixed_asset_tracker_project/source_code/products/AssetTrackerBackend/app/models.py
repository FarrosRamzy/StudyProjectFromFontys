"""
File: models.py
Author: Farros Ramzy (you@domain.com)
Description: Request and response models.
Version: 0.2
Date: 2026-04-20

Copyright (c) 2026
"""

from pydantic import BaseModel, Field, ConfigDict


class RegisterAssetRequest(BaseModel):
    tag_id: str = Field(min_length=1)
    item_name: str = Field(min_length=1)
    registration_node_id: str = Field(min_length=1)

    # User-selected first placement after registration

    initial_room_name: str = Field(min_length=1)
    initial_node_id: str = ""


class CreateMovementRequest(BaseModel):
    tag_id: str = Field(min_length=1)
    destination_room_name: str = Field(min_length=1)
    destination_node_id: str = ""
    note: str = ""


class DecideMovementRequest(BaseModel):
    movement_request_id: int
    registration_node_id: str = Field(min_length=1)


class CancelMovementRequest(BaseModel):
    movement_request_id: int


class DeregisterAssetRequest(BaseModel):
    tag_id: str = Field(min_length=1)
    registration_node_id: str = Field(min_length=1)
    reason: str = ""


class EnrollNodeRequest(BaseModel):
    device_id: str = Field(min_length=1)


class AssignNodeRequest(BaseModel):
    alias: str = ""
    role: str = Field(min_length=1)
    hospital_id: str = Field(min_length=1)
    hospital_name: str = Field(min_length=1)
    room_name: str = ""
    mqtt_host: str = Field(min_length=1)
    mqtt_port: int = Field(default=1883, alias="mqttPort")
    model_config = ConfigDict(validate_by_name=True)


class ProvisionNodeRequest(BaseModel):
    device_id: str = Field(min_length=1)


class ProvisionNodeResponse(BaseModel):
    is_provisioned: bool
    role: str = ""
    hospital_id: str = ""
    hospital_name: str = ""
    room_name: str = ""
    mqtt_host: str = ""
    mqtt_port: int = 1883


class IdentifyNodeRequest(BaseModel):
    blink_count: int = Field(default=6, ge=1, le=20)
    interval_ms: int = Field(default=150, ge=50, le=2000)


class CreateUserRequest(BaseModel):
    email: str = Field(min_length=1)
    full_name: str = Field(min_length=1)
    role: str = Field(min_length=1)
    password: str = Field(min_length=8)


class UpdateUserRoleRequest(BaseModel):
    role: str = Field(min_length=1)


class UpdateUserActiveRequest(BaseModel):
    is_active: bool


class ResetUserPasswordRequest(BaseModel):
    password: str = Field(min_length=8)


class SetupAdminRequest(BaseModel):
    email: str = Field(min_length=1)
    full_name: str = Field(min_length=1)
    password: str = Field(min_length=8)


class ChangeOwnPasswordRequest(BaseModel):
    current_password: str = Field(min_length=1)
    new_password: str = Field(min_length=8)


class LoginRequest(BaseModel):
    email: str = Field(min_length=1)
    password: str = Field(min_length=1)


class MqttSettingsRequest(BaseModel):
    broker_host: str = Field(min_length=1)
    broker_port: int = Field(default=1883, ge=1, le=65535)
    hospital_name: str = Field(min_length=1)
    tls_enabled: bool = False
    username: str = ""
    password: str = ""
    topic_namespace: str = Field(min_length=1)
    client_id: str = Field(min_length=1)
    enabled: bool = True


class UserResponse(BaseModel):
    id: int
    email: str
    full_name: str
    role: str
    is_active: bool


class LoginResponse(BaseModel):
    access_token: str
    token_type: str = "bearer"
    user: UserResponse
