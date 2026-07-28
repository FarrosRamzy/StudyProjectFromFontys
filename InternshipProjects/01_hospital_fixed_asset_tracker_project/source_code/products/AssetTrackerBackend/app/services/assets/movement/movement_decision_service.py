"""
File: movement_decision_service.py
Author: Farros Ramzy (you@domain.com)
Description: Approves or rejects asset movement requests.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from app.services.assets.movement.decision.movement_approval_writer import (
    approve_movement,
)
from app.services.assets.movement.decision.movement_decision_executor import (
    execute_movement_decision,
)
from app.services.assets.movement.decision.movement_decision_validation import (
    validate_approval_asset,
    validate_registration_node_for_approval,
    validate_registration_node_for_rejection,
    validate_rejection_asset,
)
from app.services.assets.movement.decision.movement_rejection_writer import (
    reject_movement,
)


def approve_asset_movement_request(req, user_id: int):
    return execute_movement_decision(
        req=req,
        user_id=user_id,
        success_message="movement_approved",
        validate_registration_node=validate_registration_node_for_approval,
        validate_asset=validate_approval_asset,
        write_decision=approve_movement,
    )


def reject_asset_movement_request(req, user_id: int):
    return execute_movement_decision(
        req=req,
        user_id=user_id,
        success_message="movement_rejected",
        validate_registration_node=validate_registration_node_for_rejection,
        validate_asset=validate_rejection_asset,
        write_decision=reject_movement,
    )
