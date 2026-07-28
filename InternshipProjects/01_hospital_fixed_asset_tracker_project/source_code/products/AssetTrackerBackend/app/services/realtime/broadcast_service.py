"""
File: broadcast_service.py
Author: Farros Ramzy (you@domain.com)
Description: Schedules thread-safe WebSocket broadcasts from backend worker threads.
Version: 0.1
Date: 2026-04-23

Copyright (c) 2026
"""

import asyncio
from typing import Any
from app.websocket_manager import ws_manager

_main_loop: asyncio.AbstractEventLoop | None = None


def set_main_loop(loop: asyncio.AbstractEventLoop):
    global _main_loop
    _main_loop = loop
    print("[Broadcast] Main event loop registered.")


def _on_broadcast_done(future: asyncio.Future) -> None:
    try:
        future.result()
    except Exception as exc:
        print(f"[Broadcast] Broadcast task failed: {exc}")


def schedule_broadcast(message: dict[str, Any]) -> None:
    if _main_loop is None:
        print("[Broadcast] No event loop available. Skipping broadcast.")
        return

    print(f"[Broadcast] Scheduling: {message.get('type')}")

    try:
        future = asyncio.run_coroutine_threadsafe(
            ws_manager.broadcast_json(message),
            _main_loop,
        )
        future.add_done_callback(_on_broadcast_done)
    except Exception as exc:
        print(f"[Broadcast] Failed to schedule broadcast: {exc}")
        # Broadcast can be skipped here unless the loop
        # reference is managed explicitly.
