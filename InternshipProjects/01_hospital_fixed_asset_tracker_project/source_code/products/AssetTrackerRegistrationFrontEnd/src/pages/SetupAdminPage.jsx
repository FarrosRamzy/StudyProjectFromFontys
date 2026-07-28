/**
 * @file SetupAdminPage.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-04

 * @Copyright (c) 2026
 */


import { useEffect, useState } from "react";
import { Navigate, useNavigate } from "react-router-dom";
import { useAuth } from "../context/AuthContext";
import { getSetupStatus } from "../services/setupApi";

export default function SetupAdminPage() {
    const navigate = useNavigate();
    const { setupAdmin, isAuthenticated, authLoading } = useAuth();

    const [checking, setChecking] = useState(true);
    const [setupRequired, setSetupRequired] = useState(false);
    const [fullName, setFullName] = useState("");
    const [email, setEmail] = useState("");
    const [password, setPassword] = useState("");
    const [confirmPassword, setConfirmPassword] = useState("");
    const [showPassword, setShowPassword] = useState(false);
    const [submitting, setSubmitting] = useState(false);
    const [error, setError] = useState("");

    useEffect(() => {
        let cancelled = false;

        async function checkSetupStatus() {
            try {
                const data = await getSetupStatus();

                if (!cancelled) {
                    setSetupRequired(Boolean(data.setup_required));
                }
            } catch (err) {
                if (!cancelled) {
                    setError(err.message || "Unable to check setup status.");
                }
            } finally {
                if (!cancelled) {
                    setChecking(false);
                }
            }
        }

        checkSetupStatus();

        return () => { cancelled = true; };
    }, []);

    async function handleSubmit(event) {
        event.preventDefault();
        setError("");

        if (password !== confirmPassword) {
            setError("Password confirmation does not match.");
            return;
        }

        setSubmitting(true);

        try {
            await setupAdmin({ email, full_name: fullName, password });
            navigate("/", { replace: true });
        } catch (err) {
            setError(err.message || "Unable to create administrator.");
        } finally {
            setSubmitting(false);
        }
    }

    if (!authLoading && isAuthenticated) {
        return <Navigate to="/" replace />;
    }

    if (!checking && !setupRequired && !error) {
        return <Navigate to="/login" replace />;
    }
    return (
        <main className="login-page setup-page">
            <section className="login-hero">
                <div className="login-brand">
                    <span className="brand-badge">First-Time Setup</span>
                    <h1>Create the system administrator account.</h1>
                    <p>
                        This step unlocks the hospital asset registration console.
                        After the first administrator exists, this page is disabled.
                    </p>

                    <div className="login-trust-list">
                        <span>One-Time Setup</span>
                        <span>Admin Access</span>
                        <span>Secure Registration</span>
                    </div>
                </div>
            </section>

            <section className="login-card-wrap">
                <form className="login-card" onSubmit={handleSubmit}>
                    <div>
                        <p className="eyebrow">Administrator Setup</p>
                        <h2>First admin</h2>
                        <p className="login-subtitle">
                            Create the first account that can manage this system.
                        </p>
                    </div>

                    {checking && <div className="auth-notice">Checking setup status...</div>}
                    {error && <div className="auth-error">{error}</div>}

                    <label>
                        Full name
                        <input value={fullName} onChange={(e) => setFullName(e.target.value)} required />
                    </label>

                    <label>
                        Email
                        <input type="email" value={email} onChange={(e) => setEmail(e.target.value)} required />
                    </label>

                    <label>
                        Password
                        <div className="password-field">
                            <input
                                type={showPassword ? "text" : "password"}
                                value={password}
                                onChange={(e) => setPassword(e.target.value)}
                                minLength={8}
                                required
                            />
                            <button type="button" onClick={() => setShowPassword((v) => !v)}>
                                {showPassword ? "Hide" : "Show"}
                            </button>
                        </div>
                    </label>

                    <label>
                        Confirm password
                        <input
                            type={showPassword ? "text" : "password"}
                            value={confirmPassword}
                            onChange={(e) => setConfirmPassword(e.target.value)}
                            minLength={8}
                            required
                        />
                    </label>

                    <button className="login-submit" disabled={checking || submitting}>
                        {submitting ? "Creating admin..." : "Create Administrator"}
                    </button>
                </form>
            </section>
        </main>
    );
}
