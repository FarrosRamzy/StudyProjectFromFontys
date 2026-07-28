/**
 * @file userApi.js
 * @author Farros Ramzy (you@domain.com)
 * @description User administration and password API helpers.
 * @version 1.0.0
 * @date 2026-06-04

 * @Copyright (c) 2026
 */


import { requestJson } from "./apiClient";

export const USER_ROLES = [
    { value: "admin", label: "Admin" },
    { value: "test_user", label: "Test User" },
    { value: "technician", label: "Technician" },
    { value: "registration_staff", label: "Registration Staff" },
    { value: "monitor_staff", label: "Monitor Staff" },
];

export async function listUsers() {
    return requestJson("/users");
}

export async function createUserAccount(payload) {
    return requestJson("/users", {
        method: "POST",
        body: JSON.stringify(payload),
    });
}

export async function setUserActive(userId, isActive) {
    return requestJson(`/users/${userId}/active`, {
        method: "PATCH",
        body: JSON.stringify({ is_active: isActive }),
    });
}

export async function resetUserPassword(userId, password) {
    return requestJson(`/users/${userId}/reset-password`, {
        method: "POST",
        body: JSON.stringify({ password }),
    });
}

export async function changeMyPassword(currentPassword, newPassword) {
    return requestJson("/users/me/password", {
        method: "POST",
        body: JSON.stringify({
            current_password: currentPassword,
            new_password: newPassword,
        }),
    });
}
