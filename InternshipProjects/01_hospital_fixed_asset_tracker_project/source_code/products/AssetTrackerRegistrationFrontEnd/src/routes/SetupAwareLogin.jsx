/**
 * @file SetupAwareLogin.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Redirects fresh systems to first-admin setup before login.
 * @version 1.0.0
 * @date 2026-06-04

 * @Copyright (c) 2026
 */


import { useEffect, useState } from "react";
import { Navigate } from "react-router-dom";
import LoginPage from "../pages/LoginPage";
import { getSetupStatus } from "../services/setupApi";

export default function SetupAwareLogin() {
    const [checking, setChecking] = useState(true);
    const [setupRequired, setSetupRequired] = useState(false);

    useEffect(() => {
        let cancelled = false;

        async function checkSetup() {
            try {
                const data = await getSetupStatus();

                if (!cancelled) {
                    setSetupRequired(Boolean(data.setup_required));
                }
            } catch {
                if (!cancelled) {
                    setSetupRequired(false);
                }
            } finally {
                if (!cancelled) {
                    setChecking(false);
                }
            }
        }

        checkSetup();

        return () => { cancelled = true; };
    }, []);

    if (checking) {
        return (
            <main className="login-page">
                <section className="login-card-wrap setup-loading-card">
                    <div className="login-card">
                        <p className="eyebrow">System Check</p>
                        <h2>Preparing access...</h2>
                        <p className="login-subtitle">Checking first-time setup status.</p>
                    </div>
                </section>
            </main>
        );
    }

    if (setupRequired) {
        return <Navigate to="/setup-admin" replace />;
    }

    return <LoginPage />;
}
