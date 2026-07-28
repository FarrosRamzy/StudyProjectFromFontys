/**
 * @file setupApi.js
 * @author Farros Ramzy (you@domain.com)
 * @description First-time system administrator setup API helpers.
 * @version 1.0.0
 * @date 2026-06-04

 * @Copyright (c) 2026
 */


import { API_BASE } from "./apiClient";
import { storeAuthSession } from "./authApi";

async function readJson(response) {
    return response.json().catch(() => ({}));
}

function getApiError(data, fallback) {
    return data.detail || data.message || fallback;
}

export async function getSetupStatus() {
    const response = await fetch(`${API_BASE}/auth/setup-status`, {
        headers: { Accept: "application/json" },
    });

    const data = await readJson(response);

    if (!response.ok) {
        throw new Error(getApiError(data, "Unable to check setup status."));
    }

    return data;
}

export async function setupFirstAdmin({ email, full_name, password }) {
    const response = await fetch(`${API_BASE}/auth/setup-admin`, {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
            Accept: "application/json",
        },
        body: JSON.stringify({ email, full_name, password }),
    });

    const data = await readJson(response);

    if (!response.ok) {
        throw new Error(getApiError(data, "Unable to create first admin."));
    }

    storeAuthSession(data);

    return data;
}
