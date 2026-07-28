/**
 * @file App.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Main application shell and page router for the Hospital Asset Monitor app.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { useCallback, useEffect, useState } from "react";
import { AppShell } from "./components/layout/AppShell.jsx";
import { LoadingState } from "./components/common/LoadingState.jsx";
import { Login } from "./pages/Login.jsx";
import { useAuth } from "./hooks/auth/useAuth.js";
import { useMonitorData } from "./hooks/monitor/useMonitorData.js";
import { useMonitorSocket } from "./hooks/monitor/useMonitorSocket.js";
import { APP_ROUTES } from "./constants/appRoutes.js";
import { MonitorPageContent } from "./components/app/MonitorPageContent.jsx";
import { canUseMonitorApp } from "./utils/app/monitorAccess.js";
import "./App.css";

export default function App() {
    const [activePage, setActivePage] = useState(APP_ROUTES.DASHBOARD);
    const [loginNotice, setLoginNotice] = useState("");
    const [accessError, setAccessError] = useState("");
    const {
        user, token, isAuthenticated, isAuthenticating,
        authError, login, logout,
    } = useAuth();
    const roleAllowed = canUseMonitorApp(user);

    const handleLogin = useCallback(async (credentials) => {
        setLoginNotice("");
        setAccessError("");
        const result = await login(credentials);
        if (!canUseMonitorApp(result?.user)) {
            await logout();
            const message = "Access denied. This monitor app is only available for admin and monitor staff accounts!";
            setAccessError(message);
            throw new Error(message);
        }
        return result;
    }, [login, logout]);

    const handleLogout = useCallback(async () => {
        await logout();
        setAccessError("");
        setLoginNotice("You have signed out successfully.");
    }, [logout]);

    useEffect(() => {
        if (!isAuthenticating && isAuthenticated && user && !roleAllowed) {
            logout();
            setLoginNotice("");
            setAccessError("Access denied. This monitor app is only available for admin and monitor staff accounts.");
        }
    }, [isAuthenticating, isAuthenticated, user, roleAllowed, logout]);

    const data = useMonitorData({ enabled: isAuthenticated && roleAllowed });
    const { wsStatus } = useMonitorSocket({
        enabled: isAuthenticated && roleAllowed,
        token,
        setAssets: data.setAssets,
        setNodes: data.setNodes,
        setMovementRequests: data.setMovementRequests,
        setAlerts: data.setAlerts,
        setActivity: data.setActivity,
        onConnected: data.refreshNodes,
    });

    if (isAuthenticating) return <LoadingState message="Checking login session..." />;
    if (!isAuthenticated || !roleAllowed) {
        return <Login error={accessError || authError} notice={loginNotice} onLogin={handleLogin} />;
    }

    return (
        <AppShell
            activePage={activePage}
            onNavigate={setActivePage}
            user={user}
            wsStatus={wsStatus}
            onRefresh={data.refreshAll}
            onLogout={handleLogout}
        >
            <MonitorPageContent
                activePage={activePage}
                data={data}
                loading={data.loading}
                error={data.error}
                refreshAll={data.refreshAll}
                onNavigate={setActivePage}
            />
        </AppShell>
    );
}
