/**
 * @file useRegistrationDashboardData.js
 * @author Farros Ramzy
 * @description Loads and automatically reconciles Registration Dashboard data.
 * @version 2.0.0
 * @date 2026-06-17
 */


import { useCallback, useEffect, useRef, useState } from "react";
import { fetchDashboardData } from "./dashboardDataFetchers";
import { useDashboardRefreshTriggers } from "./useDashboardRefreshTriggers";

export function useRegistrationDashboardData({
    loadAssets = true,
    loadNodes = true,
    loadMovementRequests = true,
} = {}) {
    const [assets, setAssets] = useState([]);
    const [nodes, setNodes] = useState([]);
    const [movementRequests, setMovementRequests] = useState([]);
    const [loading, setLoading] = useState(false);
    const [error, setError] = useState("");
    const mountedRef = useRef(false);
    const requestRunningRef = useRef(false);

    const refreshData = useCallback(async ({ silent = false } = {}) => {
        if (requestRunningRef.current) {
            return;
        }

        requestRunningRef.current = true;

        if (!silent) {
            setLoading(true);
            setError("");
        }

        try {
            const data = await fetchDashboardData({
                loadAssets,
                loadNodes,
                loadMovementRequests,
            });

            if (!mountedRef.current) {
                return;
            }

            setAssets(data.assets);
            setNodes(data.nodes);
            setMovementRequests(data.movementRequests);
        } catch (err) {
            if (mountedRef.current && !silent) {
                setError(err?.message || "Failed to load dashboard data.");
            }

            if (silent) {
                console.warn("[Registration Dashboard] Background refresh failed:", err);
            }
        } finally {
            requestRunningRef.current = false;

            if (!silent && mountedRef.current) {
                setLoading(false);
            }
        }
    }, [loadAssets, loadNodes, loadMovementRequests]);

    useEffect(() => {
        mountedRef.current = true;
        refreshData();

        return () => {
            mountedRef.current = false;
        };
    }, [refreshData]);

    useDashboardRefreshTriggers(refreshData);

    return { assets, nodes, movementRequests, loading, error, refreshData };
}
