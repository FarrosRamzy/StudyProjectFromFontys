/**
 * @file mqttSettingsFormatters.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


export function hospitalNameToSlug(hospitalName) {
    const slug = String(hospitalName || "")
        .trim()
        .toLowerCase()
        .replace(/[^a-z0-9]+/g, "-")
        .replace(/^-+|-+$/g, "");

    return slug || "default-hospital";
}

export function buildMqttTopicNamespace(hospitalName) {
    return `hospital/${hospitalNameToSlug(hospitalName)}`;
}

export function buildMqttClientId(hospitalName) {
    return `asset-tracker-backend-${hospitalNameToSlug(hospitalName)}`;
}

export function titleCaseHospitalId(hospitalId) {
    return String(hospitalId || "")
        .replace(/-/g, " ")
        .replace(/\b\w/g, (letter) => letter.toUpperCase());
}

export function getHospitalNameFromSettings(settings) {
    return (
        settings?.hospital_name ||
        titleCaseHospitalId(settings?.hospital_id) ||
        ""
    );
}

export function buildMqttSettingsPayload(form) {
    return {
        broker_host: String(form.brokerHost || "").trim(),
        broker_port: Number(form.brokerPort),
        hospital_name: String(form.hospitalName || "").trim(),
        tls_enabled: Boolean(form.tlsEnabled),
        username: String(form.username || "").trim(),
        password: String(form.password || ""),
        topic_namespace: buildMqttTopicNamespace(form.hospitalName),
        client_id: buildMqttClientId(form.hospitalName),
        enabled: Boolean(form.enabled),
    };
}
