"""
File: movement_decision_executor.py
Author: Farros Ramzy (you@domain.com)
Description: Shared executor for movement approval and rejection.
Version: 0.1
Date: 2026-06-12

Copyright (c) 2026
"""

from sqlalchemy.exc import SQLAlchemyError

from app.database import SessionLocal
from app.services.assets.movement.decision.movement_decision_repository import (
    find_asset_for_movement,
    find_movement_request,
    find_registration_node,
    save_movement_decision,
)
from app.services.assets.movement.decision.movement_decision_response import (
    build_movement_decision_response,
)
from app.services.assets.movement.decision.movement_decision_validation import (
    validate_movement_request_pending,
)


def execute_movement_decision(
    req,
    user_id: int,
    success_message: str,
    validate_registration_node,
    validate_asset,
    write_decision,
):
    db = SessionLocal()

    try:
        registration_node = find_registration_node(db, req.registration_node_id)
        error = validate_registration_node(registration_node)
        if error:
            return error

        movement = find_movement_request(db, req.movement_request_id)
        error = validate_movement_request_pending(movement)
        if error:
            return error

        asset = find_asset_for_movement(db, movement)
        error = validate_asset(asset)
        if error:
            return error

        write_decision(db, movement, asset, user_id)

        saved_asset = save_movement_decision(db, movement, asset)

        return build_movement_decision_response(
            message=success_message,
            asset=saved_asset,
            movement=movement,
        )

    except SQLAlchemyError as exc:
        db.rollback()
        print(f"[DB] Failed to process movement decision: {exc}")
        return {"message": "db_error"}

    finally:
        db.close()
