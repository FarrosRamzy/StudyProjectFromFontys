"""
File: utils.py
Author: Farros Ramzy (you@domain.com)
Description: System data time manager/utility
Version: 0.5
Date: 2026-04-30

Copyright (c) 2026
"""

import re
from datetime import datetime, timezone, timedelta

UTC = timezone.utc
WIB = timezone(timedelta(hours=7), name="WIB")
WITA = timezone(timedelta(hours=8), name="WITA")
WIT = timezone(timedelta(hours=9), name="WIT")


def now_utc() -> datetime:
    return datetime.now(UTC)


def now_wib() -> datetime:
    return datetime.now(WIB)


def now_wita() -> datetime:
    return datetime.now(WITA)


def now_wit() -> datetime:
    return datetime.now(WIT)


def to_wib_iso(value) -> str:
    if not value:
        return ""

    dt = parse_timestamp(value)
    return dt.astimezone(WIB).isoformat()


def to_wita_iso(value) -> str:
    if not value:
        return ""

    dt = parse_timestamp(value)
    return dt.astimezone(WITA).isoformat()


def to_wit_iso(value) -> str:
    if not value:
        return ""

    dt = parse_timestamp(value)
    return dt.astimezone(WIT).isoformat()


def parse_timestamp(value) -> datetime:
    if isinstance(value, datetime):
        if value.tzinfo is None:
            value = value.replace(tzinfo=WIB)

        return value.astimezone(WIB)

    if isinstance(value, str):
        clean = value.strip()

        if clean.endswith("Z"):
            clean = clean[:-1] + "+00:00"

        if clean.endswith("+00"):
            clean = clean[:-3] + "+00:00"

        match = re.match(r"^(.*\.\d{1,6})([+-]\d{2}:\d{2})$", clean)
        if match:
            main, tz = match.groups()
            date_part, frac = main.rsplit(".", 1)
            clean = f"{date_part}.{frac.ljust(6, '0')}{tz}"

        try:
            dt = datetime.fromisoformat(clean)

            if dt.tzinfo is None:
                dt = dt.replace(tzinfo=WIB)

            return dt.astimezone(WIB)

        except Exception as exc:
            raise ValueError(f"Invalid timestamp: {value}") from exc

    raise ValueError(f"Invalid timestamp type: {type(value)}")
