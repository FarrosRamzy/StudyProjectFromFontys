/**
 * @file webSocketEvents.js
 * @author Farros Ramzy (you@domain.com)
 * @description WebSocket event constants used by the monitor app.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


export const WS_EVENT_TYPE = {
    RAW_MESSAGE: "raw_message",

    WEBSOCKET_CONNECTED: "websocket_connected",
    WEBSOCKET_DISCONNECTED: "websocket_disconnected",

    ASSET_REGISTERED: "asset_registered",
    ASSET_UPDATED: "asset_updated",
    ASSET_DEREGISTERED: "asset_deregistered",
    ASSET_LOCATION_UPDATED: "asset_location_updated",
    ASSET_FLOW_STATUS_UPDATED: "asset_flow_status_updated",
    ASSET_DETECTED: "asset_detected",

    ASSET_MOVEMENT_REQUESTED: "asset_movement_requested",
    ASSET_MOVEMENT_APPROVED: "asset_movement_approved",
    ASSET_MOVEMENT_REJECTED: "asset_movement_rejected",
    ASSET_MOVEMENT_CANCELLED: "asset_movement_cancelled",
    ASSET_MOVEMENT_COMPLETED: "asset_movement_completed",

    MOVEMENT_REQUEST_CREATED: "movement_request_created",
    MOVEMENT_REQUEST_UPDATED: "movement_request_updated",

    NODE_REGISTERED: "node_registered",
    NODE_ENROLLED: "node_enrolled",
    NODE_ASSIGNED: "node_assigned",
    NODE_UNASSIGNED: "node_unassigned",
    NODE_UPDATED: "node_updated",
    NODE_STATUS_UPDATED: "node_status_updated",
    NODE_HEARTBEAT: "node_heartbeat",
    NODE_OFFLINE: "node_offline",
    NODE_STATUS_UNKNOWN: "node_status_unknown",
    NODE_HEARTBEAT_IGNORED: "node_heartbeat_ignored",
    DISABLED_NODE_RECONNECTED: "disabled_node_reconnected",

    UNKNOWN_TAG: "unknown_tag",
    UNKNOWN_TAG_DETECTED: "unknown_tag_detected",
    INACTIVE_ASSET_DETECTED: "inactive_asset_detected",
    UNKNOWN_NODE_DETECTION: "unknown_node_detection",
    ASSET_WRONG_LOCATION: "asset_wrong_location",
    ASSET_UNAUTHORIZED_MOVEMENT: "asset_unauthorized_movement",
};

export const ASSET_UPSERT_EVENTS = new Set([
    WS_EVENT_TYPE.ASSET_REGISTERED,
    WS_EVENT_TYPE.ASSET_UPDATED,
    WS_EVENT_TYPE.ASSET_DEREGISTERED,
    WS_EVENT_TYPE.ASSET_LOCATION_UPDATED,
    WS_EVENT_TYPE.ASSET_FLOW_STATUS_UPDATED,
    WS_EVENT_TYPE.ASSET_DETECTED,
    WS_EVENT_TYPE.ASSET_MOVEMENT_REQUESTED,
    WS_EVENT_TYPE.ASSET_MOVEMENT_APPROVED,
    WS_EVENT_TYPE.ASSET_MOVEMENT_REJECTED,
    WS_EVENT_TYPE.ASSET_MOVEMENT_CANCELLED,
    WS_EVENT_TYPE.ASSET_MOVEMENT_COMPLETED,
]);

export const NODE_UPSERT_EVENTS = new Set([
    WS_EVENT_TYPE.NODE_REGISTERED,
    WS_EVENT_TYPE.NODE_ENROLLED,
    WS_EVENT_TYPE.NODE_ASSIGNED,
    WS_EVENT_TYPE.NODE_UNASSIGNED,
    WS_EVENT_TYPE.NODE_UPDATED,
    WS_EVENT_TYPE.NODE_STATUS_UPDATED,
    WS_EVENT_TYPE.NODE_HEARTBEAT,
    WS_EVENT_TYPE.NODE_OFFLINE,
    WS_EVENT_TYPE.NODE_STATUS_UNKNOWN,
    WS_EVENT_TYPE.DISABLED_NODE_RECONNECTED,
]);

export const MOVEMENT_REQUEST_UPSERT_EVENTS = new Set([
    WS_EVENT_TYPE.MOVEMENT_REQUEST_CREATED,
    WS_EVENT_TYPE.MOVEMENT_REQUEST_UPDATED,
    WS_EVENT_TYPE.ASSET_MOVEMENT_REQUESTED,
    WS_EVENT_TYPE.ASSET_MOVEMENT_APPROVED,
    WS_EVENT_TYPE.ASSET_MOVEMENT_REJECTED,
    WS_EVENT_TYPE.ASSET_MOVEMENT_CANCELLED,
    WS_EVENT_TYPE.ASSET_MOVEMENT_COMPLETED,
]);

export const ALERT_EVENTS = new Set([
    WS_EVENT_TYPE.UNKNOWN_TAG,
    WS_EVENT_TYPE.UNKNOWN_TAG_DETECTED,
    WS_EVENT_TYPE.INACTIVE_ASSET_DETECTED,
    WS_EVENT_TYPE.UNKNOWN_NODE_DETECTION,
    WS_EVENT_TYPE.ASSET_WRONG_LOCATION,
    WS_EVENT_TYPE.ASSET_UNAUTHORIZED_MOVEMENT,
]);

export const WS_STATUS = {
    IDLE: "idle",
    CONNECTING: "connecting",
    CONNECTED: "connected",
    DISCONNECTED: "disconnected",
    ERROR: "error",
};

export const WS_STATUS_META = {
    [WS_STATUS.IDLE]: {
        label: "Idle",
        tone: "neutral",
    },
    [WS_STATUS.CONNECTING]: {
        label: "Connecting",
        tone: "warning",
    },
    [WS_STATUS.CONNECTED]: {
        label: "Connected",
        tone: "success",
    },
    [WS_STATUS.DISCONNECTED]: {
        label: "Disconnected",
        tone: "warning",
    },
    [WS_STATUS.ERROR]: {
        label: "Error",
        tone: "danger",
    },
};
