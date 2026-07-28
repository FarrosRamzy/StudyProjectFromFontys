"""
File: user_serializer.py
Author: Farros Ramzy (you@domain.com)
Description: Converts user database records into safe API response dictionaries.
Version: 0.1
Date: 2026-05-29

Copyright (c) 2026
"""

from app.db_models import User
from app.utils import to_wib_iso


def user_to_dict(user: User) -> dict:
    return {
        "id": user.id,
        "email": user.email,
        "full_name": user.full_name,
        "role": user.role,
        "is_active": user.is_active,
        "created_at": to_wib_iso(user.created_at),
        "updated_at": to_wib_iso(user.updated_at),
    }
