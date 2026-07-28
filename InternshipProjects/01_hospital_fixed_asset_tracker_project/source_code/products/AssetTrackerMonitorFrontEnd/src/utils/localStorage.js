/**
 * @file localStorage.js
 * @author Farros Ramzy (you@domain.com)
 * @description Safe storage helpers for authentication and app preferences.
 * 
 * Auth behavior:
 * - Refresh page: user stays logged in.
 * - Open another tab during the same browser session: user stays logged in.
 * - Logout: user is logged out everywhere.
 * - Fresh browser session after previous session ended: old login is cleared.
 * 
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


export const STORAGE_KEYS = {
    ACCESS_TOKEN: "asset_tracker_access_token",
    USER: "asset_tracker_user",
    ACTIVE_MONITOR_PAGE: "asset_tracker_monitor_active_page",
};

function getAuthStorage() {
    return window.sessionStorage;
}

function getPreferenceStorage() {
    return window.localStorage;
}

export function safeGetItem(key, fallback = null, storage = getAuthStorage()) {
    try {
        return storage.getItem(key) ?? fallback;
    } catch {
        return fallback;
    }
}

export function safeSetItem(key, value, storage = getAuthStorage()) {
    try {
        storage.setItem(key, value);
        return true;
    } catch {
        return false;
    }
}

export function safeRemoveItem(key, storage = getAuthStorage()) {
    try {
        storage.removeItem(key);
        return true;
    } catch {
        return false;
    }
}

export function safeGetJson(key, fallback = null, storage = getAuthStorage()) {
    try {
        const value = storage.getItem(key);
        return value ? JSON.parse(value) : fallback;
    } catch {
        return fallback;
    }
}

export function safeSetJson(key, value, storage = getAuthStorage()) {
    try {
        storage.setItem(key, JSON.stringify(value));
        return true;
    } catch {
        return false;
    }
}

export function getStoredToken() {
    return safeGetItem(STORAGE_KEYS.ACCESS_TOKEN, "", getAuthStorage());
}

export function setStoredToken(token) {
    return safeSetItem(STORAGE_KEYS.ACCESS_TOKEN, token, getAuthStorage());
}

export function clearStoredToken() {
    return safeRemoveItem(STORAGE_KEYS.ACCESS_TOKEN, getAuthStorage());
}

export function getStoredUser() {
    return safeGetJson(STORAGE_KEYS.USER, null, getAuthStorage());
}

export function setStoredUser(user) {
    return safeSetJson(STORAGE_KEYS.USER, user, getAuthStorage());
}

export function clearStoredUser() {
    return safeRemoveItem(STORAGE_KEYS.USER, getAuthStorage());
}

export function clearAuthStorage() {
    clearStoredToken();
    clearStoredUser();
}

export function getStoredActiveMonitorPage(fallback = "dashboard") {
    return safeGetItem(STORAGE_KEYS.ACTIVE_MONITOR_PAGE, fallback, getPreferenceStorage());
}

export function setStoredActiveMonitorPage(page) {
    return safeSetItem(STORAGE_KEYS.ACTIVE_MONITOR_PAGE, page, getPreferenceStorage());
}
