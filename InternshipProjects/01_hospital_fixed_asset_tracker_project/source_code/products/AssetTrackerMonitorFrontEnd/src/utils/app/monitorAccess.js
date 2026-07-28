/**
 * @file monitorAccess.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


const MONITOR_ALLOWED_ROLES = new Set([
    "admin",
    "system_admin",
    "system_administrator",
    "test_user",
    "monitor_staff",
]);

export function normalizeRole(role) {
    return String(role || "")
        .trim()
        .toLowerCase()
        .replace(/[\s-]+/g, "_");
}

export function canUseMonitorApp(user) {
    return MONITOR_ALLOWED_ROLES.has(normalizeRole(user?.role));
}
