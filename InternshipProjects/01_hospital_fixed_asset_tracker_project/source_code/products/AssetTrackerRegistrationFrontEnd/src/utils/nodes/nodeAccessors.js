/**
 * @file nodeAccessors.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-11

 * @Copyright (c) 2026
 */


import { NODE_ROLES } from "./nodeConstants";
import { normalizeNodeRole, normalizeNodeStatus } from "./nodeNormalizers";

export function getNodeIdentity(node) {
    return node?.device_id || "";
}

export function getNodeAlias(node) {
    return node?.alias || "";
}

export function getNodeDisplayName(node) {
    return node?.alias || node?.device_id || "Unnamed Node";
}

export function getNodeHospitalId(node) {
    return node?.hospital_id || "";
}

export function getNodeHospitalName(node) {
    return node?.hospital_name || "-";
}

export function getNodeRoomName(node) {
    return node?.room_name || "";
}

export function getNodeMqttHost(node) {
    return node?.mqtt_host || "";
}

export function getNodeMqttPort(node) {
    return Number(node?.mqtt_port || 1883);
}

export function getNodeRole(node) {
    return normalizeNodeRole(node?.role);
}

export function getNodeStatus(node) {
    return normalizeNodeStatus(node?.status);
}

export function getNodeLocation(node) {
    if (getNodeRole(node) === NODE_ROLES.REGISTRATION) {
        return "Registration Desk";
    }

    return node?.room_name || "-";
}

export function isCheckpointNode(node) {
    return getNodeRole(node) === NODE_ROLES.CHECKPOINT;
}

export function isRegistrationNode(node) {
    return getNodeRole(node) === NODE_ROLES.REGISTRATION;
}

export function isNodeProvisioned(node) {
    return Boolean(node?.is_provisioned);
}

export function isNodeOnline(node) {
    return getNodeStatus(node) === "ONLINE";
}

export function isNodeOffline(node) {
    return getNodeStatus(node) === "OFFLINE";
}

export function isNodeDisabled(node) {
    return getNodeStatus(node) === "DISABLED";
}

export function isNodeDiscovered(node) {
    return getNodeStatus(node) === "DISCOVERED";
}

export function isNodeAssigned(node) {
    const status = getNodeStatus(node);

    return (
        Boolean(node?.is_provisioned) ||
        status === "ASSIGNED" ||
        status === "ONLINE" ||
        status === "OFFLINE"
    );
}

export function canAssignNode(node) {
    const status = getNodeStatus(node);

    return (
        !isNodeAssigned(node) ||
        status === "DISCOVERED" ||
        status === "DISABLED"
    );
}

export function canEditNode(node) {
    return isNodeAssigned(node);
}

export function canUnassignNode(node) {
    return isNodeAssigned(node);
}

export function canDeleteNode(node) {
    const status = getNodeStatus(node);

    return (
        !isNodeAssigned(node) ||
        status === "DISCOVERED" ||
        status === "DISABLED"
    );
}

export function getNodeLabel(node) {
    if (!node) {
        return "Unknown node";
    }

    return node.alias || node.room_name || node.device_id;
}
