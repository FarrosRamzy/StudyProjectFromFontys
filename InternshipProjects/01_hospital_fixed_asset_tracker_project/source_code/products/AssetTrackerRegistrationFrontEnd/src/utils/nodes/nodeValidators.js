/**
 * @file nodeValidators.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-11

 * @Copyright (c) 2026
 */


import { NODE_ROLES } from "./nodeConstants";
import { getNodeIdentity } from "./nodeAccessors";
import { normalizeNodeRole } from "./nodeNormalizers";

export function normalizeMqttPort(port) {
    const numericPort = Number(port);

    if (!Number.isInteger(numericPort)) {
        return null;
    }

    if (numericPort < 1 || numericPort > 65535) {
        return null;
    }

    return numericPort;
}

export function validateNodeAssignmentForm({
    selectedNode,
    role,
    hospitalName,
    hospitalId,
    roomName,
    mqttHost,
    mqttPort,
}) {
    const cleanRole = normalizeNodeRole(role);

    if (!getNodeIdentity(selectedNode)) {
        return invalid("Please select a discovered node before assigning it.");
    }

    if (!cleanRole) {
        return invalid("Please choose a valid node role.");
    }

    if (!String(hospitalName || "").trim()) {
        return invalid("Please configure the hospital name in System Settings.");
    }

    if (!String(hospitalId || "").trim()) {
        return invalid("MQTT hospital ID is missing. Reload System Settings.");
    }

    if (cleanRole === NODE_ROLES.CHECKPOINT && !String(roomName || "").trim()) {
        return invalid("Checkpoint nodes require a room name.");
    }

    if (!String(mqttHost || "").trim()) {
        return invalid("MQTT broker host is missing from System Settings.");
    }

    if (normalizeMqttPort(mqttPort) === null) {
        return invalid("MQTT port must be a whole number from 1 to 65535.");
    }

    return { valid: true, message: "" };
}

export function isValidNodeAssignmentForm(formState) {
    return validateNodeAssignmentForm(formState).valid;
}

function invalid(message) {
    return { valid: false, message };
}
