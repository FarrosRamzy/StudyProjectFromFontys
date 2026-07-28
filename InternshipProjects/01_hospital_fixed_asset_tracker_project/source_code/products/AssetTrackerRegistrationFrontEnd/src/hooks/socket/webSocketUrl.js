/**
 * @file webSocketUrl.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import { API_BASE } from "../../services/apiClient";
import { getStoredToken } from "../../services/authApi";

export function apiBaseToWebSocketBase(apiBase) {
    return String(apiBase || "http://localhost:8010")
        .trim()
        .replace(/^["']|["']$/g, "")
        .replace(/^https:/i, "wss:")
        .replace(/^http:/i, "ws:")
        .replace(/\/+$/, "");
}

export function normalizeWebSocketUrl(value) {
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
    return wsUrl.endsWith("/ws") ? wsUrl : `${wsUrl}/ws`;
}

export function withAuthToken(wsUrl) {
    const token = getStoredToken();

    if (!token) {
        return null;
    }

    const separator = wsUrl.includes("?") ? "&" : "?";
    return `${wsUrl}${separator}token=${encodeURIComponent(token)}`;
}
