/**
 * @file useAuthAction.js
 * @author Farros Ramzy (you@domain.com)
 * @description Authentication action handlers for the frontend.
 * @version 1.0.0
 * @date 2026-05-18

 * @Copyright (c) 2026
 */


import { useNavigate } from "react-router-dom";
import { useAuth } from "../context/AuthContext.jsx";

export const LOGOUT_REDIRECT_KEY = "asset_tracker_logout_redirect";

export function useAuthActions() {
    const navigate = useNavigate();
    const { logout } = useAuth();

    async function handleLogout() {
        window.sessionStorage.setItem(LOGOUT_REDIRECT_KEY, "true");

        await logout();
        
        navigate("/login", { 
            replace: true,
            state: {
                reason: "signed_out"
            },  
        });
    }

    return {
        handleLogout,
    };
}