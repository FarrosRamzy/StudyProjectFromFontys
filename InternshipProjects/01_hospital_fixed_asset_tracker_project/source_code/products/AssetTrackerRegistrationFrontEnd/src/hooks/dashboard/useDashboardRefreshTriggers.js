/**
 * @file useDashboardRefreshTriggers.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import { useEffect } from "react";

const DASHBOARD_REFRESH_INTERVAL_MS = 10000;

export function useDashboardRefreshTriggers(refreshData) {
    useEffect(() => {
        const intervalId = window.setInterval(() => {
            refreshData({ silent: true });
        }, DASHBOARD_REFRESH_INTERVAL_MS);

        return () => window.clearInterval(intervalId);
    }, [refreshData]);

    useEffect(() => {
        function handleVisibilityChange() {
            if (document.visibilityState === "visible") {
                refreshData({ silent: true });
            }
        }

        document.addEventListener("visibilitychange", handleVisibilityChange);
        return () => document.removeEventListener("visibilitychange", handleVisibilityChange);
    }, [refreshData]);

    useEffect(() => {
        function handleWindowFocus() {
            refreshData({ silent: true });
        }

        window.addEventListener("focus", handleWindowFocus);
        return () => window.removeEventListener("focus", handleWindowFocus);
    }, [refreshData]);
}
