/**
 * @file useMonitorSocket.js
 * @author Farros Ramzy (you@domain.com)
 * @description WebSocket hook for realtime monitor updates.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { useEffect, useRef, useState } from "react";
import { createMonitorWebSocket, safelyCloseWebSocket, WS_STATUS } from "../../services/websocketClient";
import { addSocketActivity } from "./socket/socketActivity";
import { createMonitorMessageHandler } from "./socket/monitorSocketMessageHandler";

export function useMonitorSocket({
    enabled = true,
    setAssets,
    setNodes,
    setMovementRequests,
    setAlerts,
    setActivity,
    onConnected,
} = {}) {
    const socketRef = useRef(null);
    const reconnectTimerRef = useRef(null);
    const reconnectAttemptRef = useRef(0);
    const [wsStatus, setWsStatus] = useState(WS_STATUS.IDLE);

    useEffect(() => {
        if (!enabled) {
            setWsStatus(WS_STATUS.IDLE);
            return undefined;
        }

        let isActive = true;
        const handleMessage = createMonitorMessageHandler({
            setAssets, setNodes, setMovementRequests, setAlerts, setActivity,
        });

        function clearReconnectTimer() {
            if (reconnectTimerRef.current) window.clearTimeout(reconnectTimerRef.current);
            reconnectTimerRef.current = null;
        }

        function connect() {
            clearReconnectTimer();
            setWsStatus(WS_STATUS.CONNECTING);
            safelyCloseWebSocket(socketRef.current);
            try {
                socketRef.current = createMonitorWebSocket({
                    onOpen: () => handleOpen(isActive, reconnectAttemptRef, setWsStatus, setActivity, onConnected),
                    onMessage: (message) => isActive && handleMessage(message),
                    onClose: () => handleClose(isActive, reconnectAttemptRef, setWsStatus, reconnectTimerRef, connect),
                    onError: () => isActive && setWsStatus(WS_STATUS.ERROR),
                });
            } catch (error) {
                if (!isActive) return;
                socketRef.current = null;
                setWsStatus(WS_STATUS.ERROR);
                addSocketActivity(setActivity, "websocket_error", {
                    message: error.message || "Unable to start realtime connection.",
                });
            }
        }

        connect();
        return () => {
            isActive = false;
            clearReconnectTimer();
            safelyCloseWebSocket(socketRef.current);
            socketRef.current = null;
        };
    }, [enabled, setAssets, setNodes, setMovementRequests, setAlerts, setActivity, onConnected]);

    return { wsStatus };
}

function handleOpen(isActive, reconnectAttemptRef, setWsStatus, setActivity, onConnected) {
    if (!isActive) return;
    reconnectAttemptRef.current = 0;
    setWsStatus(WS_STATUS.CONNECTED);
    addSocketActivity(setActivity, "websocket_connected", {
        message: "Realtime connection established.",
    });
    onConnected?.();
}

function handleClose(isActive, reconnectAttemptRef, setWsStatus, reconnectTimerRef, connect) {
    if (!isActive) return;
    setWsStatus(WS_STATUS.DISCONNECTED);
    reconnectAttemptRef.current += 1;
    const delay = Math.min(1000 * reconnectAttemptRef.current, 10000);
    reconnectTimerRef.current = window.setTimeout(() => isActive && connect(), delay);
}
