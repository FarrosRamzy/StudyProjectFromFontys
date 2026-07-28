"""
File: system_setting_db_model.py
Author: Farros Ramzy (you@domain.com)
Description: System setting database model.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from sqlalchemy import Column, DateTime, String, Text

from app.database import Base
from app.utils import now_wib


class SystemSetting(Base):
    __tablename__ = "system_settings"

    key = Column(String, primary_key=True, index=True)
    value = Column(Text, nullable=False, default="")

    created_at = Column(DateTime(timezone=True), default=now_wib)
    updated_at = Column(DateTime(timezone=True), default=now_wib, onupdate=now_wib)
