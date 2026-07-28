"""
File: asset_db_model.py
Author: Farros Ramzy (you@domain.com)
Description: Asset database model.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from sqlalchemy import Column, DateTime, Integer, String, Text

from app.database import Base
from app.utils import now_wib


class Asset(Base):
    """Persistent hospital asset record."""

    __tablename__ = "assets"

    tag_id = Column(String, primary_key=True, index=True)
    hospital_id = Column(String, index=True, default="")
    item_name = Column(String)
    status = Column(String)

    registered_at = Column(DateTime(timezone=True), nullable=True)
    last_node_id = Column(String)
    last_seen_at = Column(DateTime(timezone=True), nullable=True)

    # these below for the MQTT detection updates:

    hospital_name = Column(String)
    last_room_name = Column(String)
    last_device_id = Column(String)

    # Movement / placement state:

    flow_status = Column(String, default="pending_placement")
    """Values defined by the asset flow-status constants, such as :\n
    - pending_placement
    - available
    - movement_requested
    - in_transit
    - wrong_location
    - unauthorized_movement
    """

    expected_room_name = Column(String, default="")
    expected_node_id = Column(String, default="")
    assigned_room_name = Column(String, default="")
    assigned_node_id = Column(String, default="")

    active_movement_request_id = Column(Integer, nullable=True)
    movement_note = Column(Text, default="")

    created_at = Column(DateTime(timezone=True), default=now_wib)
    updated_at = Column(DateTime(timezone=True), default=now_wib, onupdate=now_wib)

    created_by_user_id = Column(Integer, nullable=True)
    deregistered_at = Column(DateTime(timezone=True), nullable=True)
    deregistered_reason = Column(Text, default="")
