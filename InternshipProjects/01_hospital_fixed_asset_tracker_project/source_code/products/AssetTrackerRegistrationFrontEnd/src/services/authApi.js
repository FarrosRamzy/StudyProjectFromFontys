/**
 * @file authApi.js
 * @author Farros Ramzy (you@domain.com)
 * @description Authentication API and browser-session storage helpers.
 *              Behavior:
 *                  - Refresh page: stays logged in.
 *                  - Open another tab while one app tab is active: stays logged in.
 *                  - Logout: clears login.
 *                  - Close all tabs: next fresh session clears old login after stale tab heartbeat expires.
 * @version 1.0.0
 * @date 2026-05-18

 * @Copyright (c) 2026
 */


import { API_BASE } from "./apiClient";
import {
    clearAuthSession,
    getStoredToken,
    getStoredUser,
    initializeAuthSession,
    storeAuthSession,
    storeCurrentUser,
} from "./authSession";

export const AUTH_EXPIRED_EVENT = "asset-tracker-auth-expired";

export {
    clearAuthSession,
    getStoredToken,
    getStoredUser,
    initializeAuthSession,
    storeAuthSession,
};

export function notifyAuthExpired() {
    window.dispatchEvent(new Event(AUTH_EXPIRED_EVENT));
}

export async function loginUser(email, password) {
    const response = await fetch(`${API_BASE}/auth/login`, {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
            Accept: "application/json",
        },
        body: JSON.stringify({ email, password }),
    });

    const data = await response.json().catch(() => ({}));

    if (!response.ok) {
        throw new Error(data.detail || data.message || "Login failed.");
    }

    storeAuthSession(data);
    return data;
}

export async function logoutUser() {
    const token = getStoredToken();

    try {
        if (token) {
            await fetch(`${API_BASE}/auth/logout`, {
                method: "POST",
                headers: {
                    Authorization: `Bearer ${token}`,
                    Accept: "application/json",
                },
            });
        }
    } catch {
        // Local logout must still happen if the API call fails.
    } finally {
        clearAuthSession();
    }
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
        storeCurrentUser(data.user);
    }

    return data.user;
}
