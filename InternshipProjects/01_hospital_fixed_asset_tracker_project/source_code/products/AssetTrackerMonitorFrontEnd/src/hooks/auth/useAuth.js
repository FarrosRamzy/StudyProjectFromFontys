/**
 * @file useAuth.js
 * @author Farros Ramzy (you@domain.com)
 * @description Authentication state hook for the monitor app.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { useCallback, useEffect, useState } from "react";

import {
    AUTH_EXPIRED_EVENT,
    getCurrentUser,
    loginUser,
    logoutUser,
} from "../../services/authApi";

import {
    clearAuthStorage,
    getStoredToken,
    getStoredUser,
    setStoredUser,
    setStoredToken,
} from "../../utils/localStorage";

export function useAuth() {
    const [token, setToken] = useState(() => getStoredToken());
    const [user, setUser] = useState(() => getStoredUser());
    const [isAuthenticating, setIsAuthenticating] = useState(true);
    const [authError, setAuthError] = useState("");

    const isAuthenticated = Boolean(token);

    useEffect(() => {
        let isMounted = true;

        async function checkSession() {
            const storedToken = getStoredToken();

            if (!storedToken) {
                if (isMounted) {
                    setToken("");
                    setUser(null);
                    setIsAuthenticating(false);
                }

                return;
            }

            try {
                const currentUser = await getCurrentUser();
                console.log("[MonitorAuth] /auth/me user:", currentUser);
                const normalizedUser = currentUser?.user || currentUser;

                if (!isMounted) {
                    return;
                }

                if (normalizedUser?.role) {
                    setToken(storedToken);
                    setUser(normalizedUser);
                    setStoredUser(normalizedUser);
                } else {
                    clearAuthStorage();
                    setToken("");
                    setUser(null);
                }
            } catch {
                if (!isMounted) {
                    return;
                }

                clearAuthStorage();
                setToken("");
                setUser(null);
            } finally {
                if (isMounted) {
                    setIsAuthenticating(false);
                }
            }
        }

        checkSession();

        return () => {
            isMounted = false;
        };
    }, []);

    useEffect(() => {
        function handleAuthExpired() {
            clearAuthStorage();
            setToken("");
            setUser(null);
            setAuthError("Your session expired. Please sign in again.");
        }

        window.addEventListener(AUTH_EXPIRED_EVENT, handleAuthExpired);

        return () => {
            window.removeEventListener(AUTH_EXPIRED_EVENT, handleAuthExpired);
        };
    }, []);

    const login = useCallback(async ({ email, password }) => {
        setAuthError("");

        try {
            const result = await loginUser({ email, password });

            const nextToken = result?.token || result?.access_token || "";
            const nextUser = result?.user?.user || result?.user || result;

            if (!nextToken || !nextUser?.role) {
                throw new Error("Login response is missing token or user role.");
            }

            setStoredToken(nextToken);
            setStoredUser(nextUser);

            setToken(nextToken);
            setUser(nextUser);

            return {
                ...result,
                token: nextToken,
                user: nextUser,
            };
        } catch (error) {
            const message = error?.message || "Login failed.";

            setAuthError(message);

            throw error;
        }
    }, []);

    const logout = useCallback(async () => {
        await logoutUser();
        clearAuthStorage();
        setToken("");
        setUser(null);
        setAuthError("");
    }, []);

    return {
        user,
        token,
        isAuthenticated,
        isAuthenticating,
        authError,
        login,
        logout,
    };
}
