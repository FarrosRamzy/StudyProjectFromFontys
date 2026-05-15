"""
File: websocket_manager.py
Author: Farros Ramzy (you@domain.com)
Description: Description
Version: 1.0
Date: 2026-04-30

Copyright (c) 2026
"""

from typing import Any
from fastapi import WebSocket
from fastapi.encoders import jsonable_encoder


class ConnectionManager:
    """Manage active WS clients."""

    def __init__(self) -> None:
        self.connections: list[WebSocket] = []

    async def connect(self, websocket: WebSocket) -> None:
        await websocket.accept()
        self.connections.append(websocket)
        print(
            f"[WS] Client connected. Total: {len(self.connections)} "
            f"id={id(websocket)}"
        )

    def disconnect(self, websocket: WebSocket) -> None:
        if websocket in self.connections:
            self.connections.remove(websocket)
        print(
            f"[WS] Client disconnected. Total: {len(self.connections)} "
            f"id={id(websocket)}"
        )

    async def broadcast_json(self, message: dict[str, Any]) -> None:
        print(
            f"[WS] Broadcasting {message.get('type')} "
            f"to {len(self.connections)} client(s)"
        )

        encoded_message = jsonable_encoder(message)
        dead_connections: list[WebSocket] = []

        for ws in self.connections:
            try:
                await ws.send_json(encoded_message)
            except Exception as exc:
                print(f"[WS] Failed to send message: {exc}")
                dead_connections.append(ws)

        for ws in dead_connections:
            self.disconnect(ws)


ws_manager = ConnectionManager()
