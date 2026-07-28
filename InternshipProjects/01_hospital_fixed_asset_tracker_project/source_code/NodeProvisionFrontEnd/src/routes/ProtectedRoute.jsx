/**
 * @file ProtectedRoute.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-18

 * @Copyright (c) 2026
 */

import { Navigate } from "react-router-dom";
import { useAuth } from "../context/AuthContext";

export default function ProtectedRoute({ children, allowedRoles = [] }) {
    const { user, isAuthenticated, authLoading } = useAuth();

    if (authLoading) {
        return (
            <div className="page-shell">
                <div className="panel">
                    <p>Checking session...</p>
                </div>
            </div>
        );
    }

    if (!isAuthenticated) {
        return <Navigate to="/login" replace />;
    }

    if (allowedRoles.length > 0 && !allowedRoles.includes(user?.role)) {
        return (
            <div className="page-shell">
                <div className="panel">
                    <h1>Access denied</h1>
                    <p>You do not have permission to access this page.</p>
                </div>
            </div>
        );
    }

    return children;
}
