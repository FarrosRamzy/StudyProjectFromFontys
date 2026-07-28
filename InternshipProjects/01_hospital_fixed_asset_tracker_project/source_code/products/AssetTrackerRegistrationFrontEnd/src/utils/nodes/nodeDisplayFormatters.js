/**
 * @file nodeDisplayFormatters.js
 * @author Farros Ramzy (you@domain.com)
 * @description UI display formatters for node registration data.
 * @version 1.0.0
 * @date 2026-05-11
 *
 * @Copyright (c) 2026
 */


import {
    NODE_ROLE_LABELS,
    NODE_STATUS_LABELS,
} from "./nodeConstants";

import {
    getNodeDisplayName,
    getNodeHospitalName,
    getNodeIdentity,
    getNodeLocation,
    getNodeRole,
    getNodeStatus,
} from "./nodeAccessors";

import {
    normalizeNodeRole,
    normalizeNodeStatus,
} from "./nodeNormalizers";

import { formatRelativeTime } from "./nodeDateFormatters";

const NODE_STATUS_TONES = {
    DISCOVERED: "warning",
    ASSIGNED: "info",
    ONLINE: "success",
    OFFLINE: "danger",
    DISABLED: "neutral",
    ERROR: "danger",
};

const NODE_ROLE_TONES = {
    REGISTRATION: "primary",
    CHECKPOINT: "info",
};

const CONNECTION_LABELS = {
    connected: "Connected",
    connecting: "Connecting",
    disconnected: "Disconnected",
    error: "Connection Error",
};

const CONNECTION_TONES = {
    connected: "success",
    connecting: "warning",
    disconnected: "neutral",
    error: "danger",
};

function resolveRole(roleOrNode) {
    return typeof roleOrNode === "string"
        ? normalizeNodeRole(roleOrNode)
        : getNodeRole(roleOrNode);
}

function resolveStatus(statusOrNode) {
    return typeof statusOrNode === "string"
        ? normalizeNodeStatus(statusOrNode)
        : getNodeStatus(statusOrNode);
}

export function formatNodeId(node) {
    return getNodeIdentity(node) || "-";
}

export function formatShortNodeId(nodeOrId) {
    const rawId =
        typeof nodeOrId === "string"
            ? nodeOrId
            : nodeOrId?.device_id || "";

    if (!rawId) {
        return "-";
    }

    const marker = "-NODE-";
    const upperId = rawId.toUpperCase();
    const markerIndex = upperId.indexOf(marker);

    if (markerIndex === -1) {
        return rawId;
    }

    const prefixEnd = markerIndex + marker.length;
    const suffix = rawId.slice(prefixEnd);

    if (suffix.length <= 4) {
        return rawId;
    }

    return `${rawId.slice(0, prefixEnd)}${rawId.slice(-4)}`;
}

export function formatNodeName(node) {
    return getNodeDisplayName(node);
}

export function formatNodeHospital(node) {
    return getNodeHospitalName(node);
}

export function formatNodeLocation(node) {
    return getNodeLocation(node);
}

export function formatNodeRole(roleOrNode) {
    const role = resolveRole(roleOrNode);

    return NODE_ROLE_LABELS[role] || "-";
}

export function formatNodeRoleTone(roleOrNode) {
    const role = resolveRole(roleOrNode);

    return NODE_ROLE_TONES[role] || "neutral";
}

export function formatNodeStatus(statusOrNode) {
    const status = resolveStatus(statusOrNode);

    return NODE_STATUS_LABELS[status] || status || "-";
}

export function formatNodeStatusTone(statusOrNode) {
    const status = resolveStatus(statusOrNode);

    return NODE_STATUS_TONES[status] || "neutral";
}

export function formatLastPing(node) {
    return formatRelativeTime(node?.last_ping_at);
}

export function formatConnectionStatus(wsStatus) {
    const status = String(wsStatus || "").toLowerCase();

    return CONNECTION_LABELS[status] || "Unknown";
}

export function formatConnectionTone(wsStatus) {
    const status = String(wsStatus || "").toLowerCase();

    return CONNECTION_TONES[status] || "neutral";
}
