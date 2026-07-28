/**
 * @file apiClient.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-11

 * @Copyright (c) 2026
 */


const DEFAULT_API_BASE_URL = "http://localhost:8010";
const REQUEST_TIMEOUT_MS = 15000;

import {
    clearAuthSession,
    getStoredToken,
    notifyAuthExpired,
} from "./authApi";

function normalizeBaseUrl(value) {
    return String(value || DEFAULT_API_BASE_URL).replace(/\/+$/, "");
}

function normalizePath(path) {
    return String(path || "").startsWith("/") ? String(path) : `/${path}`;
}

export const API_BASE = normalizeBaseUrl(import.meta.env.VITE_API_BASE_URL);

function buildApiUrl(path) {
    return `${API_BASE}${normalizePath(path)}`;
}

async function readResponseBody(response) {
    const contentType = response.headers.get("content-type") || "";

    if (contentType.includes("application/json")) {
        try {
            return await response.json();
        } catch {
            return null;
        }
    }

    try {
        const text = await response.text();
        return text ? { message: text } : null;
    } catch {
        return null;
    }
}

function getErrorMessage(data, response) {
    if (typeof data?.detail === "string") {
        return data.detail;
    }

    if (Array.isArray(data?.detail) && data.detail.length > 0) {
        return data.detail
            .map((item) => item?.msg || item?.message || JSON.stringify(item))
            .join("; ");
    }

    return (
        data?.message ||
        data?.error ||
        `Request failed with HTTP ${response.status}`
    );
}

export async function requestJson(path, options = {}) {
    const controller = new AbortController();
    const timeoutId = setTimeout(() => controller.abort(), REQUEST_TIMEOUT_MS);
    const token = getStoredToken();

    const headers = {
        Accept: "application/json",
        ...(options.body ? { "Content-Type": "application/json" } : {}),
        ...(options.headers || {}),
    };

    if (token) {
        headers.Authorization = `Bearer ${token}`;
    }

    try {
        const response = await fetch(buildApiUrl(path), {
            ...options,
            headers,
            signal: controller.signal,
        });

        const data = await readResponseBody(response);

        if (response.status === 401) {
            clearAuthSession();
            notifyAuthExpired();
            throw new Error("Your session has expired. Please sign in again.");
        }

        if (response.status === 403) {
            throw new Error("You do not have permission to perform this action.");
        }

        if (!response.ok) {
            throw new Error(getErrorMessage(data, response));
        }

        return data;
    } catch (error) {
        if (error.name === "AbortError") {
            throw new Error(
                "Backend request timed out. Check the backend server or network connection."
            );
        }

        throw error;
    } finally {
        clearTimeout(timeoutId);
    }
}
