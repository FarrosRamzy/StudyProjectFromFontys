/**
 * @file LoginPage.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-18

 * @Copyright (c) 2026
 */

import { useState } from "react";
import { Navigate, useNavigate } from "react-router-dom";
import { useAuth } from "../context/AuthContext";

export default function LoginPage() {
    const navigate = useNavigate();
    const { login, isAuthenticated, authLoading } = useAuth();

    const [email, setEmail] = useState("");
    const [password, setPassword] = useState("");
    const [showPassword, setShowPassword] = useState(false);
    const [submitting, setSubmitting] = useState(false);
    const [error, setError] = useState("");

    async function handleSubmit(event) {
        event.preventDefault();

        setError("");
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

    if (!authLoading && isAuthenticated) {
        return <Navigate to="/" replace />;
    }

    return (
        <main className="login-page">
            <section className="login-hero">
                <div className="login-brand">
                    <span className="brand-badge">Hospital Asset Tracker</span>
                    <h1>Secure access for hospital asset operations.</h1>
                    <p>
                        Register RFID nodes, manage checkpoint devices, and protect
                        hospital asset visibility through authorized staff access.
                    </p>

                    <div className="login-trust-list">
                        <span>RFID Asset Tracking</span>
                        <span>Node Registration</span>
                        <span>Secure Monitoring</span>
                    </div>
                </div>
            </section>

            <section className="login-card-wrap">
                <form className="login-card" onSubmit={handleSubmit}>
                    <div>
                        <p className="eyebrow">Authorized Staff Only</p>
                        <h2>Sign in</h2>
                        <p className="login-subtitle">
                            Use your hospital staff account to continue.
                        </p>
                    </div>

                    {error && <div className="login-error">{error}</div>}

                    <label>
                        Email
                        <input
                            type="email"
                            value={email}
                            onChange={(event) => setEmail(event.target.value)}
                            placeholder="admin@hospital.local"
                            autoComplete="username"
                            required
                        />
                    </label>

                    <label>
                        Password
                        <div className="password-field">
                            <input
                                type={showPassword ? "text" : "password"}
                                value={password}
                                onChange={(event) => setPassword(event.target.value)}
                                placeholder="Enter your password"
                                autoComplete="current-password"
                                required
                            />
                            <button
                                type="button"
                                onClick={() => setShowPassword((current) => !current)}
                            >
                                {showPassword ? "Hide" : "Show"}
                            </button>
                        </div>
                    </label>

                    <button
                        type="submit"
                        className="login-submit"
                        disabled={submitting}
                    >
                        {submitting ? "Signing in..." : "Sign In"}
                    </button>

                    <p className="security-note">
                        Access is restricted to authorized hospital personnel.
                    </p>
                </form>
            </section>
        </main>
    );
}
