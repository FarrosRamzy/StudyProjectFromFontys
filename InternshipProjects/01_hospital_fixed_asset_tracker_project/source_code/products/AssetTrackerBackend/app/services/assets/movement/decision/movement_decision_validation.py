"""
File: movement_decision_validation.py
Author: Farros Ramzy (you@domain.com)
Description: Validation rules for movement approval and rejection.
Version: 0.1
Date: 2026-06-12

Copyright (c) 2026
"""


def validate_registration_node_for_approval(registration_node):
    if registration_node is None:
        return {"message": "registration_node_not_found"}

    if not registration_node.is_provisioned:
        return {"message": "registration_node_not_provisioned"}

    if registration_node.status == "DISABLED":
        return {"message": "registration_node_disabled"}

    if registration_node.role != "REGISTRATION":
        return {"message": "invalid_registration_node"}

    return None


def validate_registration_node_for_rejection(registration_node):
    if registration_node is None:
        return {"message": "registration_node_not_found"}

    if registration_node.role != "REGISTRATION":
        return {"message": "invalid_registration_node"}

    return None


def validate_movement_request_pending(movement):
    if movement is None:
        return {"message": "movement_request_not_found"}

    if movement.status != "pending":
        return {"message": "movement_request_not_pending"}

    return None


def validate_approval_asset(asset):
    if asset is None:
        return {"message": "asset_not_found"}

    if asset.status != "active":
        return {"message": "asset_not_active"}

    return None


def validate_rejection_asset(asset):
    if asset is None:
        return {"message": "asset_not_found"}

    return None
