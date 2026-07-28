/**
 * @file authApi.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-18

 * @Copyright (c) 2026
 */

import { API_BASE } from "./apiClient";

const TOKEN_STORAGE_KEY = "asset_tracker_access_token";
const USER_STORAGE_KEY = "asset_tracker_user";

export const AUTH_EXPIRED_EVENT = "asset-tracker-auth-expired";

export function notifyAuthExpired() {
    window.dispatchEvent(new Event(AUTH_EXPIRED_EVENT));
}

export function getStoredToken() {
    return localStorage.getItem(TOKEN_STORAGE_KEY);
}

export function getStoredUser() {
    const rawUser = localStorage.getItem(USER_STORAGE_KEY);

    if (!rawUser) {
        return null;
    }

    try {
        return JSON.parse(rawUser);
    } catch {
        return null;
    }
}

export function storeAuthSession({ access_token, user }) {
    localStorage.setItem(TOKEN_STORAGE_KEY, access_token);
    localStorage.setItem(USER_STORAGE_KEY, JSON.stringify(user));
}

export function clearAuthSession() {
    localStorage.removeItem(TOKEN_STORAGE_KEY);
    localStorage.removeItem(USER_STORAGE_KEY);
}

export async function loginUser(email, password) {
    const response = await fetch(`${API_BASE}/auth/login`, {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
            Accept: "application/json",
        },
        body: JSON.stringify({
            email,
            password,
        }),
    });

    const data = await response.json().catch(() => ({}));

    if (!response.ok) {
        throw new Error(data.detail || data.message || "Login failed.");
    }

    storeAuthSession(data);

    return data;
}

export async function fetchCurrentUser() {
    const token = getStoredToken();

    if (!token) {
        return null;
    }

    const response = await fetch(`${API_BASE}/auth/me`, {
        headers: {
            Authorization: `Bearer ${token}`,
            Accept: "application/json",
        },
    });

    if (!response.ok) {
        clearAuthSession();
        return null;
    }

    const data = await response.json();

    if (data.user) {
        localStorage.setItem(USER_STORAGE_KEY, JSON.stringify(data.user));
    }

    return data.user;
}
