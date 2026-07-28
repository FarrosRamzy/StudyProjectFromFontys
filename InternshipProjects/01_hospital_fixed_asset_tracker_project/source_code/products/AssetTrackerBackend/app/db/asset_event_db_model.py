"""
File: asset_event_db_model.py
Author: Farros Ramzy (you@domain.com)
Description: Asset event database model.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from sqlalchemy import Column, DateTime, Index, Integer, String, Text

from app.database import Base


class AssetEvent(Base):
    __tablename__ = "asset_events"

    id = Column(Integer, primary_key=True, autoincrement=True)
    hospital_id = Column(String, index=True, default="")
    tag_id = Column(String, index=True)
    device_id = Column(String, index=True)

    hospital_name = Column(String, index=True)
    room_name = Column(String)

    event_type = Column(String)
    """_summary_ :\n
    - DETECTION
    - UNKNOWN_TAG
    - REGISTER
    - DEREGISTER
    """

    timestamp = Column(DateTime(timezone=True))
    raw_payload = Column(Text, default="")

    __table_args__ = (
        Index("idx_asset_events_tag_timestamp", "tag_id", "timestamp"),
        Index("idx_asset_events_device_timestamp", "device_id", "timestamp"),
        Index("idx_asset_events_hospital_timestamp", "hospital_id", "timestamp"),
        Index("idx_asset_events_type_timestamp", "event_type", "timestamp"),
    )
