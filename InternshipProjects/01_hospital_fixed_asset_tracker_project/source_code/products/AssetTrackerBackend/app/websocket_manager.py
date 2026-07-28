"""
File: websocket_manager.py
Author: Farros Ramzy (you@domain.com)
Description: System websocket 
Version: 1.0
Date: 2026-04-30

Copyright (c) 2026
"""

from typing import Any
import asyncio

from fastapi import WebSocket
from fastapi.encoders import jsonable_encoder


class ConnectionManager:
    """Manage active WS clients."""

    def __init__(self) -> None:
        self.connections: set[WebSocket] = set()
        self._lock = asyncio.Lock()

    async def connect(self, websocket: WebSocket) -> None:
        await websocket.accept()

        async with self._lock:
            self.connections.add(websocket)
            total = len(self.connections)

        print(
            f"[WS] Client connected. Total: {total} "
            f"id={id(websocket)}"
        )

    async def disconnect(self, websocket: WebSocket) -> None:
        async with self._lock:
            self.connections.discard(websocket)
            total = len(self.connections)

        print(
            f"[WS] Client disconnected. Total: {total} "
            f"id={id(websocket)}"
        )

    async def broadcast_json(self, message: dict[str, Any]) -> None:
        async with self._lock:
            connections = list(self.connections)

        print(
            f"[WS] Broadcasting {message.get('type')} "
            f"to {len(connections)} client(s)"
        )

        encoded_message = jsonable_encoder(message)
        dead_connections: list[WebSocket] = []

        for ws in connections:
            try:
                await ws.send_json(encoded_message)
            except Exception as exc:
                print(f"[WS] Failed to send message: {exc}")
                dead_connections.append(ws)

        for ws in dead_connections:
            await self.disconnect(ws)


ws_manager = ConnectionManager()
