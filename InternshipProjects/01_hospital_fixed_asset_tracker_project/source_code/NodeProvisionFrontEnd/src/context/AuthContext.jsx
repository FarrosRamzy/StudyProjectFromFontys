/**
 * @file AuthContext.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-18

 * @Copyright (c) 2026
 */

import { createContext, useContext, useEffect, useMemo, useState } from "react";
import {
    AUTH_EXPIRED_EVENT,
    clearAuthSession,
    fetchCurrentUser,
    getStoredToken,
    getStoredUser,
    loginUser,
} from "../services/authApi";

const AuthContext = createContext(null);

export function AuthProvider({ children }) {
    const [token, setToken] = useState(() => getStoredToken());
    const [user, setUser] = useState(() => getStoredUser());
    const [authLoading, setAuthLoading] = useState(true);

    useEffect(() => {
        let cancelled = false;

        async function loadCurrentUser() {
            if (!getStoredToken()) {
                setAuthLoading(false);
                return;
            }

            const currentUser = await fetchCurrentUser();

            if (!cancelled) {
                setUser(currentUser);
                setToken(getStoredToken());
                setAuthLoading(false);
            }
        }

        loadCurrentUser();

        return () => {
            cancelled = true;
        };
    }, []);

    useEffect(() => {
        function handleAuthExpired() {
            clearAuthSession();
            setToken(null);
            setUser(null);
        }

        window.addEventListener(AUTH_EXPIRED_EVENT, handleAuthExpired);

        return () => {
            window.removeEventListener(AUTH_EXPIRED_EVENT, handleAuthExpired);
        };
    }, []);

    async function login(email, password) {
        const data = await loginUser(email, password);

        setToken(data.access_token);
        setUser(data.user);

        return data;
    }

    function logout() {
        clearAuthSession();
        setToken(null);
        setUser(null);
    }

    const value = useMemo(
        () => ({
            token,
            user,
            isAuthenticated: Boolean(token && user),
            authLoading,
            login,
            logout,
        }),
        [token, user, authLoading]
    );

    return <AuthContext.Provider value={value}>{children}</AuthContext.Provider>;

}

export function useAuth() {
    const context = useContext(AuthContext);

    if (!context) {
        throw new Error("useAuth must be used inside AuthProvider");
    }

    return context;
}
