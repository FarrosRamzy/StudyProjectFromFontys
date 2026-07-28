/**
 * @file authApi.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-20

 * @Copyright (c) 2026
 */

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