/**
 * @file useAssetRegistrationSocket.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-07

 * @Copyright (c) 2026
 */

import { useEffect, useState } from "react";
import { handleAssetSocketMessage } from "./socket/assetSocketHandlers";
import { getStoredToken } from "../services/authApi";
import { API_BASE } from "../services/apiClient";

// const WS_BASE = import.meta.env.VITE_WS_BASE_URL ?? "ws://localhost:8010/ws";
const HEARTBEAT_INTERVAL_MS = 20000;
const RECONNECT_DELAY_MS = 2000;

function apiBaseToWebSocketBase(apiBase) {
    return String(apiBase || "http://localhost:8010")
        .trim()
        .replace(/^["']|["']$/g, "")
        .replace(/^https:/i, "wss:")
        .replace(/^http:/i, "ws:")
        .replace(/\/+$/, "");
}

function normalizeWebSocketUrl(value) {
    const rawValue = String(value || "").trim().replace(/^["']|["']$/g, "");
    const fallbackBase = apiBaseToWebSocketBase(API_BASE).replace(/\/+$/, "");

    if (!rawValue) {
        return `${fallbackBase}/ws`;
    }

    let wsUrl = rawValue;

    if (wsUrl.startsWith("http://") || wsUrl.startsWith("https://")) {
        wsUrl = apiBaseToWebSocketBase(wsUrl);
    } else if (!wsUrl.startsWith("ws://") && !wsUrl.startsWith("wss://")) {
        wsUrl = `ws://${wsUrl}`;
    }

    wsUrl = wsUrl.replace(/\/+$/, "");

    if (!wsUrl.endsWith("/ws")) {
        wsUrl = `${wsUrl}/ws`;
    }

    return wsUrl;
}

const WS_URL = normalizeWebSocketUrl(
    import.meta.env.VITE_WS_BASE_URL ?? import.meta.env.VITE_WS_URL
);

function withAuthToken(wsUrl) {
    const token = getStoredToken();

    if (!token) {
        return wsUrl;
    }

    const separator = wsUrl.includes("?") ? "&" : "?";

    return `${wsUrl}${separator}token=${encodeURIComponent(token)}`;
}

export function useAssetRegistrationSocket({
    setAssets,
    setError,
    setSuccessMessage,
}) {
    const [wsStatus, setWsStatus] = useState("disconnected");
    const [latestScan, setLatestScan] = useState(null);

    const [tagId, setTagId] = useState("");
    const [selectedNodeId, setSelectedNodeId] = useState("");
    const [deregisterNodeId, setDeregisterNodeId] = useState("");

    useEffect(() => {
        let ws = null;
        let reconnectTimer = null;
        let heartbeatTimer = null;
        let manuallyClosed = false;

        const clearHeartbeat = () => {
            if (heartbeatTimer) {
                clearInterval(heartbeatTimer);
                heartbeatTimer = null;
            }
        };

        const scheduleReconnect = () => {
            if (!manuallyClosed) {
                reconnectTimer = setTimeout(connectWebSocket, RECONNECT_DELAY_MS);
            }
        };

        const startHeartbeat = () => {
            clearHeartbeat();

            heartbeatTimer = setInterval(() => {
                if (ws?.readyState === WebSocket.OPEN) {
                    ws.send("ping");
                }
            }, HEARTBEAT_INTERVAL_MS);
        };

        const handleMessage = (event) => {
            let message;

            try {
                message = JSON.parse(event.data);
            } catch {
                console.warn("[WS] Invalid JSON message:", event.data);
                return;
            }

            console.log("[WS] Message:", message);

            handleAssetSocketMessage(message, {
                setAssets,
                setLatestScan,
                setTagId,
                setSelectedNodeId,
                setDeregisterNodeId,
                setSuccessMessage,
                setError,
            });
        };

        function connectWebSocket() {
            // ws = new WebSocket(WS_BASE);
            ws = new WebSocket(withAuthToken(WS_URL));

            ws.onopen = () => {
                // console.log("[WS] Connected to:", WS_BASE);
                console.log("[WS] Connected to:", WS_URL);
                setWsStatus("connected");
                startHeartbeat();
            };

            ws.onmessage = handleMessage;

            ws.onerror = (event) => {
                console.warn("[WS] Error:", event);
                setWsStatus("error");
            };

            ws.onclose = (event) => {
                console.warn("[WS] Closed", {
                    code: event.code,
                    reason: event.reason,
                    wasClean: event.wasClean,
                });

                clearHeartbeat();
                setWsStatus("disconnected");
                scheduleReconnect();
            };
        }

        connectWebSocket();

        return () => {
            manuallyClosed = true;

            if (reconnectTimer) {
                clearTimeout(reconnectTimer);
            }

            clearHeartbeat();

            if (ws) {
                ws.close();
            }
        };
    }, [setAssets, setError, setSuccessMessage]);

    return {
        wsStatus,
        latestScan,
        tagId,
        setTagId,
        selectedNodeId,
        setSelectedNodeId,
        deregisterNodeId,
        setDeregisterNodeId,
    };
}