"""
File: models.py
Author: Farros Ramzy (you@domain.com)
Description: Description
Version: 0.2
Date: 2026-04-20

Copyright (c) 2026
"""

from pydantic import BaseModel, Field


class RegisterAssetRequest(BaseModel):
    tag_id: str = Field(min_length=1)
    item_name: str = Field(min_length=1)
    registration_node_id: str = Field(min_length=1)
    # reg_date: str = Field(min_length=1)


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
    mqtt_port: int = 1883


class ProvisionNodeRequest(BaseModel):
    """docstring for ProvisionNodeRequest."""

    device_id: str = Field(min_length=1)


class ProvisionNodeResponse(BaseModel):
    """docstring for ProvisionNodeResponse."""

    is_provisioned: bool
    role: str = ""
    hospital_id: str = ""
    hospital_name: str = ""
    room_name: str = ""
    mqtt_host: str = ""
    mqtt_port: int = 1883
