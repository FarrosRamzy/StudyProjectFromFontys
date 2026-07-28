/**
 * @file useLoginForm.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { useEffect, useState } from "react";

export function useLoginForm({ error = "", notice = "", onLogin }) {
    const [email, setEmail] = useState("");
    const [password, setPassword] = useState("");
    const [showPassword, setShowPassword] = useState(false);
    const [submitting, setSubmitting] = useState(false);
    const [slowLoading, setSlowLoading] = useState(false);
    const [localError, setLocalError] = useState("");
    const [localNotice, setLocalNotice] = useState(notice);

    useEffect(() => setLocalNotice(notice || ""), [notice]);
    useEffect(() => {
        if (error) {
            setLocalError(error);
            setLocalNotice("");
        }
    }, [error]);

    useEffect(() => {
        if (!submitting) {
            setSlowLoading(false);
            return undefined;
        }
        const timerId = window.setTimeout(() => setSlowLoading(true), 10000);
        return () => window.clearTimeout(timerId);
    }, [submitting]);

    async function submit(event) {
        event.preventDefault();
        if (submitting) return;
        const cleanEmail = email.trim().toLowerCase();
        if (!cleanEmail || !password) {
            setLocalError("Please enter your email and password.");
            setLocalNotice("");
            return;
        }
        setSubmitting(true);
        setLocalError("");
        setLocalNotice("");
        try {
            await onLogin({ email: cleanEmail, password });
        } catch (err) {
            setLocalError(err?.message || "Login failed.");
        } finally {
            setSubmitting(false);
        }
    }

    function clearMessages() {
        setLocalError("");
        setLocalNotice("");
    }

    return {
        email, setEmail, password, setPassword, showPassword, setShowPassword,
        submitting, slowLoading, errorMessage: localError || error,
        noticeMessage: !(localError || error) ? localNotice : "",
        submit, clearMessages,
    };
}
