/**
 * @file nodeFilterHelpers.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


export function getNormalizedNodeRoleGroup(role) {
    const normalized = String(role || "").trim().toUpperCase().replace(/\s+/g, "_");
    if (["REGISTRATION", "REGISTRATION_DESK", "REGISTRATION_NODE"].includes(normalized)) {
        return "registration_desk";
    }
    if (["CHECKPOINT", "CHECKPOINT_NODE"].includes(normalized)) {
        return "checkpoint_node";
    }
    return normalized.toLowerCase();
}

export function getNormalizedNodeStatusGroup(node) {
    const status = String(node?.status || "").trim().toUpperCase();
    if (["ONLINE", "ACTIVE", "CONNECTED"].includes(status)) return "ONLINE";
    if (["OFFLINE", "DISABLED"].includes(status)) return status;
    if (["DISCOVERED", "UNKNOWN", ""].includes(status) || !node?.is_provisioned) {
        return "UNKNOWN";
    }
    return status;
}
