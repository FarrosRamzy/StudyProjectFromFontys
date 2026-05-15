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
    roomName,
    mqttHost,
    mqttPort,
}) {
    const cleanRole = normalizeNodeRole(role);

    if (!getNodeIdentity(selectedNode)) {
        return {
            valid: false,
            message: "Please select a discovered node before assigning it.",
        };
    }

    if (!cleanRole) {
        return {
            valid: false,
            message: "Please choose a valid node role.",
        };
    }

    if (!String(hospitalName || "").trim()) {
        return {
            valid: false,
            message: "Please enter the hospital name.",
        };
    }

    if (cleanRole === NODE_ROLES.CHECKPOINT && !String(roomName || "").trim()) {
        return {
            valid: false,
            message: "Checkpoint nodes require a room name.",
        };
    }

    if (!String(mqttHost || "").trim()) {
        return {
            valid: false,
            message: "Please enter the MQTT broker host.",
        };
    }

    if (normalizeMqttPort(mqttPort) === null) {
        return {
            valid: false,
            message: "MQTT port must be a whole number from 1 to 65535.",
        };
    }

    return {
        valid: true,
        message: "",
    };
}

export function isValidNodeAssignmentForm(formState) {
    return validateNodeAssignmentForm(formState).valid;
}


// import { NODE_ROLES } from "./nodeConstants";
// import { getNodeIdentity } from "./nodeAccessors";
// import { normalizeNodeRole } from "./nodeNormalizers";

// export function isValidNodeAssignmentForm({
//     selectedNode,
//     role,
//     hospitalName,
//     roomName,
//     mqttHost,
// }) {
//     const cleanRole = normalizeNodeRole(role);

//     if (!getNodeIdentity(selectedNode)) {
//         return false;
//     }

//     if (!cleanRole) {
//         return false;
//     }

//     if (!String(hospitalName || "").trim()) {
//         return false;
//     }

//     if (!String(mqttHost || "").trim()) {
//         return false;
//     }

//     if (cleanRole === NODE_ROLES.CHECKPOINT && !String(roomName || "").trim()) {
//         return false;
//     }

//     return true;
// }
// 