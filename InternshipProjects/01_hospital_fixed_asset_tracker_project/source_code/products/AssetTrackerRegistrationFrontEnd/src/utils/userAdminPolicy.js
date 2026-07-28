/**
 * @file userAdminPolicy.js
 * @author Farros Ramzy (you@domain.com)
 * @description Frontend safety rules for admin account actions.
 * @version 1.0.0
 * @date 2026-06-05

 * @Copyright (c) 2026
 */


export function normalizeRole(role) {
    return String(role || "").trim().toLowerCase().replace(/[\s-]+/g, "_");
}

export function isAdmin(user) {
    return normalizeRole(user?.role) === "admin";
}

export function getActiveAdminCount(users) {
    return users.filter((item) => isAdmin(item) && item.is_active).length;
}

export function getUserAdminPolicy({ targetUser, currentUser, users }) {
    const targetIsSelf = Number(targetUser?.id) === Number(currentUser?.id);
    const targetIsAdmin = isAdmin(targetUser);
    const activeAdminCount = getActiveAdminCount(users);
    const targetIsLastActiveAdmin = targetIsAdmin && targetUser?.is_active && activeAdminCount <= 1;

    const canDisable = Boolean(targetUser?.is_active) && !targetIsSelf && !targetIsLastActiveAdmin;
    const canEnable = Boolean(targetUser) && !targetUser?.is_active;
    const canToggleActive = canEnable || canDisable;
    const canResetPassword = Boolean(targetUser?.id) && !targetIsSelf;

    return {
        targetIsSelf,
        targetIsLastActiveAdmin,
        canToggleActive,
        canResetPassword,
        toggleReason: getToggleReason(targetIsSelf, targetIsLastActiveAdmin),
        resetReason: targetIsSelf ? "Use Change Password for your own account." : "",
    };
}

function getToggleReason(targetIsSelf, targetIsLastActiveAdmin) {
    if (targetIsSelf) {
        return "You cannot disable your own account.";
    }

    if (targetIsLastActiveAdmin) {
        return "At least one active admin is required.";
    }

    return "";
}
