"""
File: user_query_service.py
Author: Farros Ramzy (you@domain.com)
Description: Retrieves and lists user records for account-management operations.
Version: 0.1
Date: 2026-05-29

Copyright (c) 2026
"""

from app.database import SessionLocal
from app.db_models import User
from app.services.users.user_serializer import user_to_dict


def list_user_records():
    db = SessionLocal()

    try:
        users = db.query(User).order_by(User.id.asc()).all()
        return [user_to_dict(user) for user in users]

    finally:
        db.close()


def get_user_record_by_id(user_id: int):
    db = SessionLocal()

    try:
        user = db.query(User).filter(User.id == user_id).first()

        if user is None:
            return None

        return user_to_dict(user)

    finally:
        db.close()
