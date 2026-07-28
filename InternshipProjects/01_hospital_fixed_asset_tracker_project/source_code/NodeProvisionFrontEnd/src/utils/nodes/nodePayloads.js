/**
 * @file nodePayloads.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-11

 * @Copyright (c) 2026
 */

import { NODE_ROLES } from "./nodeConstants";
import { normalizeNodeRole } from "./nodeNormalizers";
import { normalizeMqttPort } from "./nodeValidators";

export function hospitalNameToId(hospitalName) {
    const safeId = String(hospitalName || "")
        .trim()
        .toLowerCase()
        .replace(/[^a-z0-9]+/g, "-")
        .replace(/^-+|-+$/g, "");

    return safeId || "imh-hospital";
}

export function buildNodeAssignmentPayload({
    alias,
    role,
    hospitalName,
    roomName,
    mqttHost,
    mqttPort,
}) {
    const cleanRole = normalizeNodeRole(role);
    const cleanHospitalName = String(hospitalName || "").trim();
    const cleanMqttPort = normalizeMqttPort(mqttPort) || 1883;

    return {
        alias: String(alias || "").trim(),
        role: cleanRole,
        hospital_id: hospitalNameToId(cleanHospitalName),
        hospital_name: cleanHospitalName,
        room_name:
            cleanRole === NODE_ROLES.CHECKPOINT
                ? String(roomName || "").trim()
                : "",
        mqtt_host: String(mqttHost || "").trim(),
        mqtt_port: cleanMqttPort,
    };
}
