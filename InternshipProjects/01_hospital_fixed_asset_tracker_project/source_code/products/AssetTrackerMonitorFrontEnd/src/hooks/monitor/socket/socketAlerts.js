/**
 * @file socketAlerts.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


export function makeSocketAlert(type, payload) {
    const alertPayload = payload.payload || payload;
    return {
        id: `${type}-${Date.now()}-${Math.random().toString(16).slice(2)}`,
        type,
        severity: type === "asset_unauthorized_movement" ? "critical" : "warning",
        title: alertPayload.title || alertPayload.item_name || alertPayload.tag_id || formatEventTitle(type),
        message: alertPayload.message || getDefaultAlertMessage(type, alertPayload),
        payload: alertPayload,
        createdAt: alertPayload.timestamp || alertPayload.createdAt || new Date().toISOString(),
    };
}

export function formatEventTitle(type) {
    return String(type || "alert")
        .replace(/_/g, " ")
        .replace(/\b\w/g, (letter) => letter.toUpperCase());
}

function getDefaultAlertMessage(type, payload) {
    if (["unknown_tag", "unknown_tag_detected"].includes(type)) {
        return `Unknown RFID tag detected: ${payload.tag_id || "-"}`;
    }
    if (type === "inactive_asset_detected") {
        return `Inactive asset detected: ${payload.tag_id || "-"}`;
    }
    if (type === "unknown_node_detection") {
        return `Detection from unknown node: ${payload.device_id || "-"}`;
    }
    if (type === "asset_wrong_location") {
        return payload.movement_note || "Asset detected in the wrong location.";
    }
    if (type === "asset_unauthorized_movement") {
        return payload.movement_note || "Unauthorized asset movement detected.";
    }
    return formatEventTitle(type);
}
