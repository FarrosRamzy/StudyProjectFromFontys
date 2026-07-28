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
    clearAuthSession,
    notifyAuthExpired,
} from "../../services/authApi";
import { handleNodeSocketMessage } from "./nodeSocketMessageHandlers";
import { normalizeWebSocketUrl, withAuthToken } from "../socket/webSocketUrl";

const HEARTBEAT_INTERVAL_MS = 20000;
const RECONNECT_BASE_DELAY_MS = 2000;
const RECONNECT_MAX_DELAY_MS = 30000;
const WS_URL = normalizeWebSocketUrl(
    import.meta.env.VITE_WS_BASE_URL ?? import.meta.env.VITE_WS_URL
);

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
            reconnectTimer = setTimeout(connectWebSocket, getReconnectDelay(reconnectAttempt));
        }

        function connectWebSocket() {
            clearReconnectTimer();
            clearHeartbeat();
            setWsStatus("connecting");

            const authenticatedWsUrl = withAuthToken(WS_URL);

            if (!authenticatedWsUrl) {
                setWsStatus("unauthenticated");
                setError("Please sign in before using live connection.");
                return;
            }

            try {
                ws = new WebSocket(authenticatedWsUrl);
            } catch (error) {
                setWsStatus("error");
                setError(`Invalid WebSocket URL: ${WS_URL}. ${error.message}`);
                scheduleReconnect();
                return;
            }

            ws.onopen = () => {
                reconnectAttempt = 0;
                setWsStatus("connected");
                heartbeatTimer = setInterval(() => {
                    if (ws?.readyState === WebSocket.OPEN) {
                        ws.send("ping");
                    }
                }, HEARTBEAT_INTERVAL_MS);
            };

            ws.onmessage = (event) => {
                const message = parseNodeSocketMessage(event.data);

                if (message) {
                    handleNodeSocketMessage(message, {
                        setNodes,
                        setError,
                        setSuccessMessage,
                    });
                }
            };

            ws.onerror = () => setWsStatus("error");
            ws.onclose = (event) => {
                clearHeartbeat();

                if (event.code === 1008) {
                    clearAuthSession();
                    notifyAuthExpired();
                    return;
                }

                setWsStatus("disconnected");
                scheduleReconnect();
            };
        }

        connectWebSocket();

        return () => {
            manuallyClosed = true;
            clearReconnectTimer();
            clearHeartbeat();
            ws?.close();
        };
    }, [setNodes, setError, setSuccessMessage]);

    return { wsStatus };
}

function parseNodeSocketMessage(data) {
    try {
        return JSON.parse(data);
    } catch {
        return null;
    }
}
