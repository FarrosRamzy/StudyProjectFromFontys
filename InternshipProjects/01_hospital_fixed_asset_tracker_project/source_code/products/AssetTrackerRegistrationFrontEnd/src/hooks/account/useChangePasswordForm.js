/**
 * @file useChangePasswordForm.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import { useState } from "react";
import { changeMyPassword } from "../../services/userApi";

export function useChangePasswordForm() {
    const [currentPassword, setCurrentPassword] = useState("");
    const [newPassword, setNewPassword] = useState("");
    const [confirmPassword, setConfirmPassword] = useState("");
    const [showNewPasswords, setShowNewPasswords] = useState(false);
    const [saving, setSaving] = useState(false);
    const [error, setError] = useState("");
    const [successMessage, setSuccessMessage] = useState("");

    async function handleSubmit(event) {
        event.preventDefault();
        setError("");
        setSuccessMessage("");

        if (newPassword !== confirmPassword) {
            setError("Password confirmation does not match.");
            return;
        }

        setSaving(true);
        try {
            await changeMyPassword(currentPassword, newPassword);
            setCurrentPassword("");
            setNewPassword("");
            setConfirmPassword("");
            setSuccessMessage("Password changed successfully.");
        } catch (err) {
            setError(err.message || "Unable to change password.");
        } finally {
            setSaving(false);
        }
    }

    return {
        currentPassword,
        setCurrentPassword,
        newPassword,
        setNewPassword,
        confirmPassword,
        setConfirmPassword,
        showNewPasswords,
        setShowNewPasswords,
        saving,
        error,
        successMessage,
        handleSubmit,
    };
}
