"""
File: db_models.py
Author: Farros Ramzy (you@domain.com)
Description: Description
Version: 0.1
Date: 2026-04-21

Copyright (c) 2026
"""

from sqlalchemy import Column, String, Boolean, Integer, DateTime, Text
from app.database import Base


class Node(Base):
    """docstring for Node."""

    __tablename__ = "nodes"

    device_id = Column(String, primary_key=True, index=True)
    hospital_id = Column(String, index=True, default="")
    alias = Column(String, default="")
    hospital_name = Column(String)
    room_name = Column(String)
    mqtt_host = Column(String)
    mqtt_port = Column(Integer, default=1883)

    is_provisioned = Column(Boolean, default=False)
    # True - after adding room detail
    # False - before adding room detail

    role = Column(String)
    # CHECKPOINT
    # REGISTRATION

    status = Column(String)
    # State choices:
    # DISCOVERED
    # ASSIGNED
    # ONLINE
    # OFFLINE
    # DISABLED
    # ERROR

    last_ping_at = Column(DateTime(timezone=True))
    last_event_at = Column(DateTime(timezone=True))
    last_message = Column(String)


class Asset(Base):
    """docstring for Node."""

    __tablename__ = "assets"

    tag_id = Column(String, primary_key=True, index=True)
    hospital_id = Column(String, index=True, default="")
    item_name = Column(String)
    status = Column(String)
    registered_at = Column(DateTime(timezone=True), nullable=True)
    last_node_id = Column(String)
    last_seen_at = Column(DateTime(timezone=True), nullable=True)

    # these below for the MQTT detection updates
    hospital_name = Column(String)
    last_room_name = Column(String)
    last_device_id = Column(String)


class AssetEvent(Base):
    __tablename__ = "asset_events"

    id = Column(Integer, primary_key=True, autoincrement=True)
    hospital_id = Column(String, index=True, default="")
    tag_id = Column(String, index=True)
    device_id = Column(String, index=True)
    hospital_name = Column(String, index=True)
    room_name = Column(String)
    event_type = Column(String)
    # DETECTION
    # UNKNOWN_TAG
    # REGISTER
    # DEREGISTER
    timestamp = Column(DateTime(timezone=True))
    raw_payload = Column(Text, default="")
