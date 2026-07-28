/**
 * @file websocketClient.js
 * @author Farros Ramzy (you@domain.com)
 * @description WebSocket client helper for realtime monitor updates.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { getStoredToken } from "../utils/localStorage";

const WS_BASE_URL = import.meta.env.VITE_WS_BASE_URL || "ws://localhost:8010/ws";

export const WS_STATUS = {
    IDLE: "idle",
    CONNECTING: "connecting",
    CONNECTED: "connected",
    DISCONNECTED: "disconnected",
    ERROR: "error",
};

function buildWebSocketUrl() {
    const token = getStoredToken();

    if (!token) {
        return null;
    }

    const separator = WS_BASE_URL.includes("?") ? "&" : "?";

    return `${WS_BASE_URL}${separator}token=${encodeURIComponent(token)}`;
}

export function createMonitorWebSocket({
    onOpen,
    onMessage,
    onClose,
    onError,
} = {}) {
    const url = buildWebSocketUrl();

    if (!url) {
        throw new Error("Missing WebSocket auth token.");
    }

    const socket = new WebSocket(url);

    socket.addEventListener("open", (event) => {
        onOpen?.(event);
    });

    socket.addEventListener("message", (event) => {
        if (event.data === "pong" || event.data === "ping") {
            return;
        }

        try {
            const data = JSON.parse(event.data);
            onMessage?.(data, event);
        } catch {
            onMessage?.(
                {
                    type: "raw_message",
                    payload: event.data,
                },
                event
            );
        }
    });

    socket.addEventListener("close", (event) => {
        onClose?.(event);
    });

    socket.addEventListener("error", (event) => {
        onError?.(event);
    });

    return socket;
}

export function safelyCloseWebSocket(socket) {
    if (!socket) {
        return;
    }

    if (
        socket.readyState === WebSocket.OPEN ||
        socket.readyState === WebSocket.CONNECTING
    ) {
        socket.close();
    }
}

export function sendWebSocketMessage(socket, message) {
    if (!socket || socket.readyState !== WebSocket.OPEN) {
        return false;
    }

    socket.send(JSON.stringify(message));
    return true;
}
