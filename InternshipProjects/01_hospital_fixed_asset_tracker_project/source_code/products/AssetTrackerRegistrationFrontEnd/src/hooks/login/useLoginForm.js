/**
 * @file useLoginForm.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import { useEffect, useState } from "react";

export function useLoginForm({ location, navigate, login }) {
    const [email, setEmail] = useState("");
    const [password, setPassword] = useState("");
    const [showPassword, setShowPassword] = useState(false);
    const [submitting, setSubmitting] = useState(false);
    const [error, setError] = useState(() => getInitialError(location));
    const [notice, setNotice] = useState(() => getInitialNotice(location));

    useEffect(() => {
        if (location.state?.reason) {
            navigate(location.pathname, { replace: true, state: null });
        }
    }, [location.pathname, location.state, navigate]);

    async function handleSubmit(event) {
        event.preventDefault();
        setError("");
        setNotice("");
        setSubmitting(true);

        try {
            await login(email, password);
            navigate("/", { replace: true });
        } catch (err) {
            setError(err.message || "Unable to sign in.");
        } finally {
            setSubmitting(false);
        }
    }

    return {
        email,
        setEmail,
        password,
        setPassword,
        showPassword,
        setShowPassword,
        submitting,
        error,
        notice,
        handleSubmit,
    };
}

function getInitialError(location) {
    return location.state?.reason === "access_denied"
        ? "Access denied. Please sign in with an authorized account."
        : "";
}

function getInitialNotice(location) {
    return location.state?.reason === "signed_out"
        ? "You have signed out successfully."
        : "";
}
