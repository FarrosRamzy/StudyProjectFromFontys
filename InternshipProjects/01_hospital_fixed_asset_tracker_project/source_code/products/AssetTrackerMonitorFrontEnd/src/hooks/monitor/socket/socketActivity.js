/**
 * @file socketActivity.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { SILENT_ACTIVITY_EVENTS } from "./socketEventSets";

export function getEventType(message) {
    return message?.type || message?.event || message?.event_type || "";
}

export function getPayload(message) {
    return message?.payload || message?.data || message || {};
}

export function makeActivityItem(type, payload) {
    return {
        id: `${type}-${Date.now()}-${Math.random().toString(16).slice(2)}`,
        type,
        message: getActivityMessage(type, payload),
        payload,
        createdAt: new Date().toISOString(),
    };
}

export function addSocketActivity(setActivity, type, payload) {
    if (SILENT_ACTIVITY_EVENTS.has(type)) return;
    setActivity?.((current) => [makeActivityItem(type, payload), ...current].slice(0, 100));
}

function getActivityMessage(type, payload) {
    if (payload?.item_name || payload?.tag_id) {
        return `${type}: ${payload.item_name || payload.tag_id}`;
    }
    if (payload?.device_id || payload?.node_id) {
        return `${type}: ${payload.device_id || payload.node_id}`;
    }
    return payload?.message || type;
}
