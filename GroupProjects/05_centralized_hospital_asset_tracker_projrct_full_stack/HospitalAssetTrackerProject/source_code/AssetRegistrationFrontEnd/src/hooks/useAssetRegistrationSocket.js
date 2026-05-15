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

const WS_BASE = import.meta.env.VITE_WS_BASE_URL ?? "ws://localhost:8010/ws";
const HEARTBEAT_INTERVAL_MS = 20000;
const RECONNECT_DELAY_MS = 2000;

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
            ws = new WebSocket(WS_BASE);

            ws.onopen = () => {
                console.log("[WS] Connected to:", WS_BASE);
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