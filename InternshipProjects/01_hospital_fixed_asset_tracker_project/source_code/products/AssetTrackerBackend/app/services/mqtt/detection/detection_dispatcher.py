"""
File: detection_dispatcher.py
Author: Farros Ramzy (you@domain.com)
Description: Routes asset location update results to detection cases.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from app.services.mqtt.detection.detection_cases import (
    handle_duplicate_detection,
    handle_inactive_asset,
    handle_stale_detection,
    handle_unknown_result_status,
    handle_unknown_tag,
    handle_updated_asset,
)


def dispatch_detection_result(result: dict, context: dict) -> None:
    result_status = result.get("status")
    asset = result.get("asset")

    if result_status == "unknown":
        handle_unknown_tag(context)
        return

    if result_status == "inactive":
        handle_inactive_asset(context, asset)
        return

    if result_status == "stale":
        handle_stale_detection(context)
        return

    if result_status == "duplicate":
        handle_duplicate_detection(context)
        return

    if result_status == "updated":
        context["movement_completed"] = bool(result.get("movement_completed"))
        context["completed_movement_request_id"] = result.get(
            "completed_movement_request_id"
        )

        handle_updated_asset(context, asset)
        return

    handle_unknown_result_status(result_status)


def _attach_update_metadata(result: dict, context: dict) -> None:
    context["previous_flow_status"] = result.get("previous_flow_status", "")
    context["previous_movement_request_id"] = result.get("previous_movement_request_id")
    context["movement_completed"] = bool(result.get("movement_completed"))
    context["completed_movement_request_id"] = result.get(
        "completed_movement_request_id"
    )
