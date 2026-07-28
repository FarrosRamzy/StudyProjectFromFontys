/**
 * @file nodeRegistrationHandlerHelpers.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import { NODE_ROLES } from "../../utils/nodeHelpers";

function normalizeText(value) {
    return String(value || "").trim();
}

function normalizeRole(value) {
    return String(value || "").trim().toUpperCase();
}

export function isDangerousNodeReassignment({ selectedNode, role, hospitalName, roomName }) {
    if (!selectedNode?.is_provisioned) {
        return false;
    }

    const oldRole = normalizeRole(selectedNode.role);
    const newRole = normalizeRole(role);
    const oldHospitalName = normalizeText(selectedNode.hospital_name);
    const newHospitalName = normalizeText(hospitalName);
    const oldRoomName = normalizeText(selectedNode.room_name);
    const newRoomName = newRole === NODE_ROLES.CHECKPOINT ? normalizeText(roomName) : "";

    return oldRole !== newRole || oldHospitalName !== newHospitalName || oldRoomName !== newRoomName;
}

export function confirmDangerousNodeReassignment() {
    return window.confirm(
        "You are changing an already-provisioned node.\n\n" +
        "Changing a node's role, room, or hospital can affect active asset tracking.\n" +
        "The backend will block this action if active assets or movement requests still reference this node.\n\n" +
        "Continue?"
    );
}
