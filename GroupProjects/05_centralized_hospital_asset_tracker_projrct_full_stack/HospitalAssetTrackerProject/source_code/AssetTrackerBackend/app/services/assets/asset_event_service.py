"""
File: asset_event_service.py
Author: Farros Ramzy (you@domain.com)
Description: Description
Version: 0.1
Date: 2026-04-27

Copyright (c) 2026
"""

import json
from datetime import datetime
from typing import Any

from sqlalchemy.exc import OperationalError

from app.database import SessionLocal
from app.db_models import AssetEvent
from app.utils import now_wib


def create_asset_event(
    *,
    tag_id: str,
    device_id: str = "",
    hospital_id: str = "",
    hospital_name: str = "",
    room_name: str = "",
    event_type: str,
    timestamp: datetime | None = None,
    raw_payload: dict[str, Any] | None = None,
) -> AssetEvent | None:
    db = SessionLocal()
    try:
        event = AssetEvent(
            tag_id=tag_id or "",
            device_id=device_id or "",
            hospital_id=hospital_id or "",
            hospital_name=hospital_name or "",
            room_name=room_name or "",
            event_type=event_type,
            timestamp=timestamp or now_wib(),
            raw_payload=json.dumps(raw_payload or {}, default=str),
        )
        
        db.add(event)
        db.commit()
        db.refresh(event)
        return event
    
    except OperationalError as exc:
        db.rollback()
        print(f"[DB] Operational error while creating asset event: {exc}")
        return None

    except Exception as exc:
        db.rollback()
        print(f"[DB] Failed to create asset event: {exc}")
        return None
    
    finally:
        db.close()
