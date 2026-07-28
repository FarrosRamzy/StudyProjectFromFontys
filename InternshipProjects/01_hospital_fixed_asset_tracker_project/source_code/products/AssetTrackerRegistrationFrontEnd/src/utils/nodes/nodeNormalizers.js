/**
 * @file nodeNormalizers.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-11

 * @Copyright (c) 2026
 */


import { NODE_ROLES, NODE_STATUSES } from "./nodeConstants";

export function normalizeNodeRole(role) {
    const cleanRole = String(role || "").trim().toUpperCase();

    if (
        cleanRole === "REGISTRATION" ||
        cleanRole === "REGISTRATION_DESK" ||
        cleanRole === "REGISTER" ||
        cleanRole === "DESK"
    ) {
        return NODE_ROLES.REGISTRATION;
    }

    if (
        cleanRole === "CHECKPOINT" ||
        cleanRole === "CHECKPOINT_NODE" ||
        cleanRole === "ROOM" ||
        cleanRole === "GATE"
    ) {
        return NODE_ROLES.CHECKPOINT;
    }

    return "";
}

export function normalizeNodeStatus(status) {
    const cleanStatus = String(status || "").trim().toUpperCase();

    if (!cleanStatus) {
        return "";
    }

    if (["CONNECTED", "ACTIVE", "OK"].includes(cleanStatus)) {
        return NODE_STATUSES.ONLINE;
    }

    if (["DISCONNECTED", "INACTIVE", "LOST"].includes(cleanStatus)) {
        return NODE_STATUSES.OFFLINE;
    }

    if (Object.values(NODE_STATUSES).includes(cleanStatus)) {
        return cleanStatus;
    }

    return cleanStatus;
}

export function normalizeNode(node) {
    if (!node) {
        return null;
    }

    return {
        device_id: node.device_id || "",
        alias: node.alias || "",
        role: normalizeNodeRole(node.role),
        hospital_id: node.hospital_id || "",
        hospital_name: node.hospital_name || "",
        room_name: node.room_name || "",
        mqtt_host: node.mqtt_host || "",
        mqtt_port: Number(node.mqtt_port || 1883),
        is_provisioned: Boolean(node.is_provisioned),
        status: normalizeNodeStatus(node.status),
        last_ping_at: node.last_ping_at || "",
        last_event_at: node.last_event_at || "",
        last_message: node.last_message || "",
    };
}

export function normalizeNodes(nodes) {
    if (!Array.isArray(nodes)) {
        return [];
    }

    return nodes.map(normalizeNode).filter(Boolean);
}