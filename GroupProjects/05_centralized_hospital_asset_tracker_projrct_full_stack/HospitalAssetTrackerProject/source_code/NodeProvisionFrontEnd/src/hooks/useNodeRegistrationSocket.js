/**
 * @file useNodeRegistrationSocket.js
 * @author Farros Ramzy (you@domain.com)
 * @description WebSocket connection for live node registration updates.
 * @version 1.0.0
 * @date 2026-05-11

 * @Copyright (c) 2026
 */

import { useEffect, useState } from "react";
import {
    normalizeNodes,
    removeNodeById,
    upsertNode,
} from "../utils/nodeHelpers";
import { API_BASE } from "../services/apiClient";

const HEARTBEAT_INTERVAL_MS = 20000;
const RECONNECT_BASE_DELAY_MS = 2000;
const RECONNECT_MAX_DELAY_MS = 30000;

function apiBaseToWebSocketBase(apiBase) {
    return String(apiBase || "http://localhost:8010")
        .replace(/^https:/i, "wss:")
        .replace(/^http:/i, "ws:");
}

// const WS_BASE =
//     import.meta.env.VITE_WS_BASE_URL ??
//     import.meta.env.VITE_WS_URL ??
//     "ws://localhost:8010/ws";

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

function getMessageNode(message) {
    return message?.node || message?.payload?.node || null;
}

function getMessageNodes(message) {
    return message?.nodes || message?.payload?.nodes || [];
}

function getDeletedDeviceId(message) {
    return (
        message?.device_id ||
        message?.payload?.device_id ||
        message?.node?.device_id ||
        message?.payload?.node?.device_id ||
        ""
    );
}

function getReconnectDelay(attempt) {
    return Math.min(
        RECONNECT_BASE_DELAY_MS * Math.max(1, attempt),
        RECONNECT_MAX_DELAY_MS
    );
}

export function useNodeRegistrationSocket({
    setNodes,
    setError,
    setSuccessMessage,
}) {
    const [wsStatus, setWsStatus] = useState("disconnected");

    useEffect(() => {
        let ws = null;
        let reconnectTimer = null;
        let heartbeatTimer = null;
        let reconnectAttempt = 0;
        let manuallyClosed = false;

        function clearHeartbeat() {
            if (heartbeatTimer) {
                clearInterval(heartbeatTimer);
                heartbeatTimer = null;
            }
        }

        function clearReconnectTimer() {
            if (reconnectTimer) {
                clearTimeout(reconnectTimer);
                reconnectTimer = null;
            }
        }

        function scheduleReconnect() {
            if (manuallyClosed) {
                return;
            }

            clearReconnectTimer();
            reconnectAttempt += 1;

            reconnectTimer = setTimeout(() => {
                connectWebSocket();
            }, getReconnectDelay(reconnectAttempt));
        }

        function connectWebSocket() {
            clearReconnectTimer();
            clearHeartbeat();
            setWsStatus("connecting");

            // ws = new WebSocket(WS_BASE);
            try {
                ws = new WebSocket(WS_BASE);
            } catch (error) {
                setWsStatus("error");
                setError(`Invalid WebSocket URL: ${WS_URL}`);
                scheduleReconnect();
                return;
            }

            ws.onopen = () => {
                reconnectAttempt = 0;
                setWsStatus("connected");

                heartbeatTimer = setInterval(() => {
                    if (ws && ws.readyState === WebSocket.OPEN) {
                        ws.send("ping");
                    }
                }, HEARTBEAT_INTERVAL_MS);
            };

            ws.onmessage = (event) => {
                let message;

                try {
                    message = JSON.parse(event.data);
                } catch {
                    return;
                }

                const messageType = message?.type;

                if (messageType === "snapshot") {
                    const snapshotNodes = getMessageNodes(message);

                    if (Array.isArray(snapshotNodes)) {
                        // setNodes(snapshotNodes);
                        setNodes(normalizeNodes(snapshotNodes));
                    }

                    return;
                }

                if (
                    messageType === "node_enrolled" ||
                    messageType === "node_assigned" ||
                    messageType === "node_unassigned" ||
                    messageType === "node_heartbeat" ||
                    messageType === "node_offline" ||
                    messageType === "disabled_node_reconnected" ||
                    messageType === "node_status_unknown"
                ) {
                    const node = getMessageNode(message);

                    if (node) {
                        setNodes((currentNodes) => upsertNode(currentNodes, node));
                    }

                    if (messageType === "node_enrolled") {
                        setSuccessMessage("New node enrolled.");
                    }

                    if (messageType === "node_assigned") {
                        setSuccessMessage("Node assigned successfully.");
                    }

                    if (messageType === "node_unassigned") {
                        setSuccessMessage("Node unassigned successfully.");
                    }

                    return;
                }

                if (messageType === "node_deleted") {
                    const deletedDeviceId = getDeletedDeviceId(message);

                    setNodes((currentNodes) =>
                        removeNodeById(currentNodes, deletedDeviceId)
                    );

                    setSuccessMessage("Node deleted successfully.");
                    return;
                }

                if (messageType === "node_heartbeat_ignored") {
                    return;
                }

                if (messageType === "error" || messageType === "node_error") {
                    setError(message.message || "Node WebSocket error received.");
                }
            };

            ws.onerror = () => {
                setWsStatus("error");
            };

            ws.onclose = () => {
                clearHeartbeat();
                setWsStatus("disconnected");
                scheduleReconnect();

                // if (!manuallyClosed) {
                //     reconnectTimer = setTimeout(() => {
                //         connectWebSocket();
                //     }, 2000);
                // }
            };
        }

        connectWebSocket();

        return () => {
            manuallyClosed = true;

            // if (reconnectTimer) {
            //     clearTimeout(reconnectTimer);
            // }

            clearReconnectTimer();
            clearHeartbeat();

            if (ws) {
                ws.close();
            }
        };
    }, [setNodes, setError, setSuccessMessage]);

    return {
        wsStatus,
    };
}