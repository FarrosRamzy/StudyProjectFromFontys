"""
File: user_db_model.py
Author: Farros Ramzy (you@domain.com)
Description: User database model.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from sqlalchemy import Boolean, Column, DateTime, Integer, String

from app.database import Base
from app.utils import now_wib


class User(Base):
    __tablename__ = "users"

    id = Column(Integer, primary_key=True, index=True)
    email = Column(String, unique=True, index=True, nullable=False)
    full_name = Column(String, nullable=False)
    role = Column(String, nullable=False, default="monitor_staff")
    hashed_password = Column(String, nullable=False)
    is_active = Column(Boolean, default=True)

    created_at = Column(DateTime(timezone=True), default=now_wib)
    updated_at = Column(DateTime(timezone=True), default=now_wib, onupdate=now_wib)
