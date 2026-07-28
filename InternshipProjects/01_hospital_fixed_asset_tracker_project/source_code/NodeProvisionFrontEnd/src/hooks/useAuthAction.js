/**
 * @file useAuthAction.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-18

 * @Copyright (c) 2026
 */

/**
 * @file useAuthActions.js
 * @description Authentication action handlers for the frontend.
 */

import { useNavigate } from "react-router-dom";
import { useAuth } from "../context/AuthContext.jsx";

export function useAuthActions() {
    const navigate = useNavigate();
    const { logout } = useAuth();

    function handleLogout() {
        logout();
        navigate("/login", { replace: true });
    }

    return {
        handleLogout,
    };
}