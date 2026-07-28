/**
 * @file useUserManagement.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import { useCallback, useEffect, useState } from "react";

import {
    createUserAccount,
    listUsers,
    resetUserPassword,
    setUserActive,
} from "../../services/userApi";

export const EMPTY_USER_FORM = {
    full_name: "",
    email: "",
    password: "",
    role: "monitor_staff",
};

export function useUserManagement() {
    const [users, setUsers] = useState([]);
    const [form, setForm] = useState(EMPTY_USER_FORM);
    const [resetPasswords, setResetPasswords] = useState({});
    const [visibleResetPasswords, setVisibleResetPasswords] = useState({});
    const [showCreatePassword, setShowCreatePassword] = useState(false);
    const [loading, setLoading] = useState(true);
    const [saving, setSaving] = useState(false);
    const [error, setError] = useState("");
    const [successMessage, setSuccessMessage] = useState("");

    const refreshUsers = useCallback(async () => {
        setLoading(true);
        try {
            const data = await listUsers();
            setUsers(Array.isArray(data) ? data : data.users || []);
        } catch (err) {
            setError(err.message || "Unable to load users.");
        } finally {
            setLoading(false);
        }
    }, []);

    useEffect(() => {
        refreshUsers();
    }, [refreshUsers]);

    function updateForm(field, value) {
        setForm((current) => ({ ...current, [field]: value }));
    }

    async function handleCreateUser(event) {
        event.preventDefault();
        setSaving(true);
        setError("");
        setSuccessMessage("");

        try {
            await createUserAccount(form);
            setForm(EMPTY_USER_FORM);
            setSuccessMessage("User account created.");
            await refreshUsers();
        } catch (err) {
            setError(err.message || "Unable to create user.");
        } finally {
            setSaving(false);
        }
    }

    async function handleResetPassword(targetUser) {
        const password = resetPasswords[targetUser.id] || "";

        if (password.length < 8) {
            setError("New password must be at least 8 characters.");
            return;
        }

        await resetUserPassword(targetUser.id, password);
        setResetPasswords((current) => ({ ...current, [targetUser.id]: "" }));
        setSuccessMessage(`Password reset for ${targetUser.email}.`);
    }

    async function handleToggleActive(targetUser) {
        await setUserActive(targetUser.id, !targetUser.is_active);
        await refreshUsers();
    }

    function toggleResetPasswordVisibility(userId) {
        setVisibleResetPasswords((current) => ({
            ...current,
            [userId]: !current[userId],
        }));
    }

    return {
        users,
        form,
        setForm,
        resetPasswords,
        setResetPasswords,
        visibleResetPasswords,
        showCreatePassword,
        setShowCreatePassword,
        loading,
        saving,
        error,
        successMessage,
        refreshUsers,
        updateForm,
        handleCreateUser,
        handleResetPassword,
        handleToggleActive,
        toggleResetPasswordVisibility,
    };
}
