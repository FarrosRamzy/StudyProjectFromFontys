"""
File: asset_flow_movement_requested.py
Author: Farros Ramzy (you@domain.com)
Description: Resolves asset flow while movement request waits for approval.
Version: 0.1
Date: 2026-06-12

Copyright (c) 2026
"""


def resolve_movement_requested_flow(db, asset, context: dict) -> None:
    if context["assigned_location_matches"]:
        asset.movement_note = (
            f"Movement request is waiting for approval. "
            f"Asset is still at {context['assigned_location_label']}."
        )
        return

    asset.flow_status = "unauthorized_movement"
    asset.movement_note = (
        f"Asset moved before approval. "
        f"Expected to remain at {context['assigned_location_label']}, "
        f"but detected at {context['detected_location_label']}."
    )
