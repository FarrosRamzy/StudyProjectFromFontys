"""
File: node_db_model.py
Author: Farros Ramzy (you@domain.com)
Description: Node database model.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from sqlalchemy import Boolean, Column, DateTime, Integer, String

from app.database import Base
from app.utils import now_wib


class Node(Base):
    """Persistent registration-desk or checkpoint-node record."""

    __tablename__ = "nodes"

    device_id = Column(String, primary_key=True, index=True)
    hospital_id = Column(String, index=True, default="")
    alias = Column(String, default="")
    hospital_name = Column(String)
    room_name = Column(String)
    mqtt_host = Column(String)
    mqtt_port = Column(Integer, default=1883)

    is_provisioned = Column(Boolean, default=False)
    """Provisioning summary :\n
    - True - after adding room detail
    - False - before adding room detail
    """

    role = Column(String)
    """System Role only contains :\n
    - CHECKPOINT
    - REGISTRATION
    """

    status = Column(String)
    """Available status for system :\n
    - DISCOVERED
    - ASSIGNED
    - ONLINE
    - OFFLINE
    - DISABLED
    - ERROR
    """

    last_ping_at = Column(DateTime(timezone=True))
    last_event_at = Column(DateTime(timezone=True))
    last_message = Column(String)

    created_at = Column(DateTime(timezone=True), default=now_wib)
    updated_at = Column(DateTime(timezone=True), default=now_wib, onupdate=now_wib)
    firmware_version = Column(String, default="")
    ip_address = Column(String, default="")
    signal_quality = Column(String, default="")
    last_boot_at = Column(DateTime(timezone=True), nullable=True)
