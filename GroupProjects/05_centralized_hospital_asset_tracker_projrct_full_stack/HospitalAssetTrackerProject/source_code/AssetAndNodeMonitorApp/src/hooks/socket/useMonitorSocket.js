/**
 * @file useMonitorSocket.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-12

 * @Copyright (c) 2026
 */

import { useEffect, useState } from "react";
import { handleMonitorSocketMessage } from "./monitorSocketHandlers";

const WS_BASE = import.meta.env.VITE_WS_BASE_URL ?? "ws://localhost:8010/ws";
const HEARTBEAT_INTERVAL_MS = 20000;
const RECONNECT_DELAY_MS = 2000;

export function useMonitorSocket({
    setAssets,
    setNodes,
    setAlerts,
    setActivity,
}) {
    const [wsStatus, setWsStatus] = useState("disconnected");

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

        const scheduleReconnect = () => {
            if (!manuallyClosed) {
                reconnectTimer = setTimeout(connectWebSocket, RECONNECT_DELAY_MS);
            }
        };

        const handleMessage = (event) => {
            let message;

            try {
                message = JSON.parse(event.data);
            } catch {
                console.warn("[WS] Invalid JSON:", event.data);
                return;
            }

            handleMonitorSocketMessage(message, {
                setAssets,
                setNodes,
                setAlerts,
                setActivity,
            });
        };

        function connectWebSocket() {
            ws = new WebSocket(WS_BASE);

            ws.onopen = () => {
                console.log("[WS] Monitor connected:", WS_BASE);
                setWsStatus("connected");
                startHeartbeat();
            };

            ws.onmessage = handleMessage;

            ws.onerror = (event) => {
                console.warn("[WS] Monitor error:", event);
                setWsStatus("error");
            };

            ws.onclose = (event) => {
                console.warn("[WS] Monitor closed:", {
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
    }, [setAssets, setNodes, setAlerts, setActivity]);

    return {
        wsStatus,
    };
}