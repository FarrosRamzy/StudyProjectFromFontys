/**
 * @file settingsApi.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { requestJson } from "./apiClient";

export async function getMqttSettings() {
    const data = await requestJson("/settings/mqtt");
    return data?.settings || data || {};
}

export async function updateMqttSettings(payload) {
    return requestJson("/settings/mqtt", {
        method: "PUT",
        body: JSON.stringify(payload),
    });
}

export async function reconnectMqtt() {
    return requestJson("/settings/mqtt/reconnect", {
        method: "POST",
    });
}

export async function resetMqttSettings() {
    return requestJson("/settings/mqtt/reset-default", {
        method: "POST",
    });
}
