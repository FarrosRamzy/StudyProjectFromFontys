"""
File: movement_decision_response.py
Author: Farros Ramzy (you@domain.com)
Description: Response builders for movement decisions.
Version: 0.1
Date: 2026-06-12

Copyright (c) 2026
"""


from app.serializers.asset_serializer import asset_to_dict


def build_movement_decision_response(message: str, asset, movement) -> dict:
    return {
        "message": message,
        "asset": asset_to_dict(asset),
        "movement_request_id": movement.id,
    }
