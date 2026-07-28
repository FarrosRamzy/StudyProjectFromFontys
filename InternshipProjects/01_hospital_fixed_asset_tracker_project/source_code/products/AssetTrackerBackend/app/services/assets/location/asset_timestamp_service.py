"""
File: asset_timestamp_service.py
Author: Farros Ramzy (you@domain.com)
Description: Normalizes asset detection timestamps for reliable chronological comparisons.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from app.utils import parse_timestamp


def normalize_asset_timestamp(value):
    if value is None:
        return None

    return parse_timestamp(value)
