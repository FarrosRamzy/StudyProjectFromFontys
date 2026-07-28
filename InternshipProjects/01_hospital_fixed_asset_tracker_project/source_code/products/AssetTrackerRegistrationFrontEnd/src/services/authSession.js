/**
 * @file authSession.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


const TOKEN_STORAGE_KEY = "asset_tracker_access_token";
const USER_STORAGE_KEY = "asset_tracker_user";
const AUTH_SESSION_MARKER = "asset_tracker_browser_session_active";
const AUTH_TAB_ID_KEY = "asset_tracker_auth_tab_id";
const ACTIVE_TABS_KEY = "asset_tracker_active_tabs";
const HEARTBEAT_INTERVAL_MS = 3000;
const STALE_TAB_MS = 9000;

let heartbeatTimer = null;

function getAuthStorage() {
    return window.localStorage;
}

function getSessionStorage() {
    return window.sessionStorage;
}

function getTabId() {
    let tabId = getSessionStorage().getItem(AUTH_TAB_ID_KEY);

    if (!tabId) {
        tabId = window.crypto?.randomUUID?.() ||
            `tab-${Date.now()}-${Math.random().toString(16).slice(2)}`;
        getSessionStorage().setItem(AUTH_TAB_ID_KEY, tabId);
    }

    return tabId;
}

function markBrowserSessionActive() {
    getSessionStorage().setItem(AUTH_SESSION_MARKER, "true");
}

function isCurrentTabSessionActive() {
    return getSessionStorage().getItem(AUTH_SESSION_MARKER) === "true";
}

function readActiveTabs() {
    const rawValue = getAuthStorage().getItem(ACTIVE_TABS_KEY);

    if (!rawValue) {
        return {};
    }

    try {
        return JSON.parse(rawValue) || {};
    } catch {
        return {};
    }
}

function writeActiveTabs(activeTabs) {
    getAuthStorage().setItem(ACTIVE_TABS_KEY, JSON.stringify(activeTabs));
}

function cleanupStaleTabs() {
    const now = Date.now();
    const cleanTabs = Object.fromEntries(
        Object.entries(readActiveTabs()).filter(([, lastSeen]) => {
            return now - Number(lastSeen || 0) <= STALE_TAB_MS;
        })
    );

    writeActiveTabs(cleanTabs);
    return cleanTabs;
}

function hasLiveTabs() {
    return Object.keys(cleanupStaleTabs()).length > 0;
}

export function updateCurrentTabHeartbeat() {
    const activeTabs = cleanupStaleTabs();
    activeTabs[getTabId()] = Date.now();
    writeActiveTabs(activeTabs);
}

function startAuthHeartbeat() {
    if (heartbeatTimer) {
        return;
    }

    updateCurrentTabHeartbeat();
    heartbeatTimer = window.setInterval(updateCurrentTabHeartbeat, HEARTBEAT_INTERVAL_MS);
}

export function initializeAuthSession() {
    const currentTabAlreadyActive = isCurrentTabSessionActive();
    const anotherTabIsAlive = hasLiveTabs();

    if (!currentTabAlreadyActive && !anotherTabIsAlive) {
        getAuthStorage().removeItem(TOKEN_STORAGE_KEY);
        getAuthStorage().removeItem(USER_STORAGE_KEY);
    }

    markBrowserSessionActive();
    startAuthHeartbeat();
}

export function getStoredToken() {
    return getAuthStorage().getItem(TOKEN_STORAGE_KEY);
}

export function getStoredUser() {
    const rawUser = getAuthStorage().getItem(USER_STORAGE_KEY);

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
    markBrowserSessionActive();
    updateCurrentTabHeartbeat();
    getAuthStorage().setItem(TOKEN_STORAGE_KEY, access_token);
    getAuthStorage().setItem(USER_STORAGE_KEY, JSON.stringify(user));
}

export function storeCurrentUser(user) {
    markBrowserSessionActive();
    updateCurrentTabHeartbeat();
    getAuthStorage().setItem(USER_STORAGE_KEY, JSON.stringify(user));
}

export function clearAuthSession() {
    getAuthStorage().removeItem(TOKEN_STORAGE_KEY);
    getAuthStorage().removeItem(USER_STORAGE_KEY);
    getAuthStorage().removeItem(ACTIVE_TABS_KEY);
    getSessionStorage().removeItem(AUTH_SESSION_MARKER);
    getSessionStorage().removeItem(AUTH_TAB_ID_KEY);

    if (heartbeatTimer) {
        window.clearInterval(heartbeatTimer);
        heartbeatTimer = null;
    }
}
