/**
 * @file userFormatters.js
 * @author Farros Ramzy (you@domain.com)
 * @description User display formatting helpers.
 * @version 1.0.0
 * @date 2026-05-29

 * @Copyright (c) 2026
 */


import { normalizeRole } from "./userAdminPolicy";

export function formatRoleLabel(role) {
    const labels = {
        admin: "Admin",
        test_user: "Test User",
        technician: "Technician",
        registration_staff: "Registration Staff",
        monitor_staff: "Monitor Staff",
    };

    return labels[normalizeRole(role)] || "User";
}

export function getDisplayName(user) {
    return user?.full_name || user?.email || "User";
}

export function canAccessDashboard(role) {
    return Boolean(normalizeRole(role));
}

export function canAccessNodeRegistration(role) {
    return ["admin", "test_user", "technician"].includes(normalizeRole(role));
}

export function canAccessAssetRegistration(role) {
    return ["admin", "test_user", "registration_staff"].includes(
        normalizeRole(role)
    );
}

export function canAccessUserManagement(role) {
    return normalizeRole(role) === "admin";
}

export function canAccessSystemSettings(role) {
    return ["admin", "test_user"].includes(normalizeRole(role));
}

export function canAccessPasswordChange(role) {
    return Boolean(normalizeRole(role));
}
