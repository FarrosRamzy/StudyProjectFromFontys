/**
 * @file useAssetRegistrationSocket.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-07

 * @Copyright (c) 2026
 */


import { useEffect, useState } from "react";
import { handleAssetSocketMessage } from "../socket/assetSocketHandlers";
import { normalizeWebSocketUrl, withAuthToken } from "../socket/webSocketUrl";

const HEARTBEAT_INTERVAL_MS = 20000;
const RECONNECT_DELAY_MS = 2000;
const WS_URL = normalizeWebSocketUrl(
    import.meta.env.VITE_WS_BASE_URL ?? import.meta.env.VITE_WS_URL
);

export function useAssetRegistrationSocket({
    setAssets,
    setError,
    setSuccessMessage,
    onMovementRequestChanged,
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

        const startHeartbeat = () => {
            clearHeartbeat();
            heartbeatTimer = setInterval(() => {
                if (ws?.readyState === WebSocket.OPEN) {
                    ws.send("ping");
                }
            }, HEARTBEAT_INTERVAL_MS);
        };

        const handleMessage = (event) => {
            if (event.data === "pong" || event.data === "ping") {
                return;
            }

            const message = parseSocketMessage(event.data);
            if (!message) {
                return;
            }

            handleAssetSocketMessage(message, {
                setAssets,
                setLatestScan,
                setTagId,
                setSelectedNodeId,
                setDeregisterNodeId,
                setSuccessMessage,
                setError,
                onMovementRequestChanged,
            });
        };

        function connectWebSocket() {
            const authenticatedWsUrl = withAuthToken(WS_URL);

            if (!authenticatedWsUrl) {
                setWsStatus("unauthenticated");
                setError("Please sign in before using live connection.");
                return;
            }

            ws = new WebSocket(authenticatedWsUrl);
            ws.onopen = () => {
                setWsStatus("connected");
                startHeartbeat();
            };
            ws.onmessage = handleMessage;
            ws.onerror = () => setWsStatus("error");
            ws.onclose = () => {
                clearHeartbeat();
                setWsStatus("disconnected");
                if (!manuallyClosed) {
                    reconnectTimer = setTimeout(connectWebSocket, RECONNECT_DELAY_MS);
                }
            };
        }

        connectWebSocket();

        return () => {
            manuallyClosed = true;
            if (reconnectTimer) clearTimeout(reconnectTimer);
            clearHeartbeat();
            ws?.close();
        };
    }, [setAssets, setError, setSuccessMessage, onMovementRequestChanged]);

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

function parseSocketMessage(data) {
    try {
        return JSON.parse(data);
    } catch {
        console.warn("[WS] Invalid JSON message:", data);
        return null;
    }
}
