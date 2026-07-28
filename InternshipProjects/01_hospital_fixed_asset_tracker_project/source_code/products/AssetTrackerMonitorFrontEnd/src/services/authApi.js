/**
 * @file authApi.js
 * @author Farros Ramzy (you@domain.com)
 * @description Authentication API helpers.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { apiRequest } from "./apiClient";
import {
    clearAuthStorage,
    getStoredToken,
    setStoredToken,
    setStoredUser,
} from "../utils/localStorage";

export const AUTH_EXPIRED_EVENT = "asset_tracker_auth_expired";

export async function getCurrentUser() {
    return apiRequest("/auth/me");
}

export async function loginUser({ email, password }) {
    const data = await apiRequest("/auth/login", {
        method: "POST",
        body: JSON.stringify({
            email: String(email || "").trim().toLowerCase(),
            password: String(password || ""),
        }),
    });

    const token =
        data?.access_token ||
        data?.token ||
        data?.accessToken ||
        "";

    if (!token) {
        throw new Error(
            "Login succeeded, but the backend did not return an access token."
        );
    }

    setStoredToken(token);

    let user =
        data?.user ||
        data?.current_user ||
        null;

    // Important:
    // Some backends only return a token from /auth/login.
    // In that case, fetch the user from /auth/me after storing the token.
    if (!user) {
        user = await getCurrentUser();
    }

    if (!user) {
        clearAuthStorage();
        throw new Error("Login succeeded, but the user profile could not be loaded.");
    }

    setStoredUser(user);

    return {
        token,
        user,
        raw: data,
    };
}

export async function logoutUser() {
    const token = getStoredToken();

    try {
        if (token) {
            await apiRequest("/auth/logout", {
                method: "POST",
            });
        }
    } catch {
        // Ignore logout API errors.
        // The frontend should still clear the local session.
    } finally {
        clearAuthStorage();
    }
}

export function notifyAuthExpired() {
    window.dispatchEvent(new Event(AUTH_EXPIRED_EVENT));
}
