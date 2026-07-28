/**
 * @file apiClient.js
 * @author Farros Ramzy (you@domain.com)
 * @description Shared API request helper for the monitor app.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import {
    clearAuthStorage,
    getStoredToken,
} from "../utils/localStorage";

const API_BASE_URL = import.meta.env.VITE_API_BASE_URL || "http://localhost:8010";

function buildUrl(path) {
    if (path.startsWith("http://") || path.startsWith("https://")) {
        return path;
    }

    const cleanBase = API_BASE_URL.replace(/\/+$/, "");
    const cleanPath = path.startsWith("/") ? path : `/${path}`;

    return `${cleanBase}${cleanPath}`;
}

async function parseResponseBody(response) {
    const contentType = response.headers.get("content-type") || "";

    if (contentType.includes("application/json")) {
        return response.json();
    }

    const text = await response.text();

    if (!text) {
        return null;
    }

    return text;
}

function getErrorMessage(data, fallback = "API request failed.") {
    if (!data) {
        return fallback;
    }

    if (typeof data === "string") {
        return data;
    }

    if (typeof data.detail === "string") {
        return data.detail;
    }

    if (Array.isArray(data.detail)) {
        return data.detail
            .map((item) => item?.msg || item?.message || JSON.stringify(item))
            .join(", ");
    }

    if (typeof data.message === "string") {
        return data.message;
    }

    if (typeof data.reason === "string") {
        return data.reason;
    }

    return fallback;
}

export async function apiRequest(path, options = {}) {
    const token = getStoredToken();

    const hasBody = options.body !== undefined && options.body !== null;

    const headers = {
        Accept: "application/json",
        ...(hasBody ? { "Content-Type": "application/json" } : {}),
        ...(token ? { Authorization: `Bearer ${token}` } : {}),
        ...(options.headers || {}),
    };

    const controller = new AbortController();
    const timeoutId = window.setTimeout(() => {
        controller.abort();
    }, 25000);

    try {
        const response = await fetch(buildUrl(path), {
            ...options,
            headers,
            signal: controller.signal,
        });

        const data = await parseResponseBody(response);

        if (!response.ok) {
            if (response.status === 401) {
                clearAuthStorage();

                window.dispatchEvent(new Event("asset_tracker_auth_expired"));
            }

            const message = getErrorMessage(
                data,
                `Request failed with status ${response.status}.`
            );

            const error = new Error(message);
            error.status = response.status;
            error.data = data;

            throw error;
        }

        return data;
    } catch (error) {
        if (error?.name === "AbortError") {
            throw new Error(
                "The backend is taking too long to respond. Please wait a moment and try again."
            );
        }

        throw error;
    } finally {
        window.clearTimeout(timeoutId);
    }
}

export function getApiBaseUrl() {
    return API_BASE_URL;
}
