"""
File: asset_movement_request_db_model.py
Author: Farros Ramzy (you@domain.com)
Description: Asset movement request database model.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from sqlalchemy import Column, DateTime, Integer, String, Text

from app.database import Base
from app.utils import now_wib


class AssetMovementRequest(Base):
    __tablename__ = "asset_movement_requests"

    id = Column(Integer, primary_key=True, autoincrement=True)

    hospital_id = Column(String, index=True, default="")
    hospital_name = Column(String, default="")

    tag_id = Column(String, index=True)
    item_name = Column(String, default="")

    from_room_name = Column(String, default="")
    from_node_id = Column(String, default="")

    destination_room_name = Column(String, index=True)
    destination_node_id = Column(String, default="")

    status = Column(String, index=True)
    """_summary_ :\n
    - pending
    - approved
    - rejected
    - completed
    - cancelled
    """

    requested_by_user_id = Column(Integer, nullable=True)
    approved_by_user_id = Column(Integer, nullable=True)

    requested_at = Column(DateTime(timezone=True), default=now_wib)
    approved_at = Column(DateTime(timezone=True), nullable=True)
    completed_at = Column(DateTime(timezone=True), nullable=True)
    rejected_at = Column(DateTime(timezone=True), nullable=True)

    note = Column(Text, default="")
