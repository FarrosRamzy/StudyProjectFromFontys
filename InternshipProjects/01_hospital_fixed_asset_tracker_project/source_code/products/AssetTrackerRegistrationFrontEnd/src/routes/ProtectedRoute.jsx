/**
 * @file ProtectedRoute.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Role-aware route guard.
 * @version 1.0.0
 * @date 2026-06-04

 * @Copyright (c) 2026
 */


import { useEffect } from "react";
import { Navigate, useLocation } from "react-router-dom";
import { useAuth } from "../context/AuthContext";
import { LOGOUT_REDIRECT_KEY } from "../hooks/useAuthAction";
import { normalizeRole } from "../utils/userAdminPolicy";

function consumeLogoutRedirectReason() {
    const logoutRedirect =
        window.sessionStorage.getItem(LOGOUT_REDIRECT_KEY) === "true";

    if (logoutRedirect) {
        window.sessionStorage.removeItem(LOGOUT_REDIRECT_KEY);
        return "signed_out";
    }

    return "";
}

export default function ProtectedRoute({ children, allowedRoles = [] }) {
    const { user, isAuthenticated, authLoading, logout } = useAuth();
    const location = useLocation();

    const roleIsAllowed =
        allowedRoles.length === 0 ||
        allowedRoles.includes(normalizeRole(user?.role));

    useEffect(() => {
        if (!authLoading && isAuthenticated && user && !roleIsAllowed) {
            logout();
        }
    }, [authLoading, isAuthenticated, user, roleIsAllowed, logout]);

    if (authLoading) {
        return <div>Loading...</div>;
    }

    if (!isAuthenticated || !user) {
        const reason = consumeLogoutRedirectReason();

        return (
            <Navigate
                to="/login"
                replace
                state={{
                    ...(reason ? { reason } : {}),
                    from: location.pathname,
                }}
            />
        );
    }

    if (!roleIsAllowed) {
        return (
            <Navigate
                to="/login"
                replace
                state={{
                    reason: "access_denied",
                    from: location.pathname,
                }}
            />
        );
    }

    return children;
}
