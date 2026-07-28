/**
 * @file useMonitorData.js
 * @author Farros Ramzy (you@domain.com)
 * @description Fetches and stores monitor data from backend APIs.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { useCallback, useEffect, useMemo, useState } from "react";
import {
    loadActiveAssetsSnapshot,
    loadMonitorSnapshot,
    loadNodesSnapshot,
} from "./data/monitorDataLoaders";
import { buildMonitorSummary } from "./data/monitorSummary";

const NODE_RECONCILIATION_INTERVAL_MS = 10000;
const ASSET_RECONCILIATION_INTERVAL_MS = 10000;

export function useMonitorData({ enabled = true } = {}) {
    const [assets, setAssets] = useState([]);
    const [nodes, setNodes] = useState([]);
    const [movementRequests, setMovementRequests] = useState([]);
    const [alerts, setAlerts] = useState([]);
    const [activity, setActivity] = useState([]);
    const [loading, setLoading] = useState(Boolean(enabled));
    const [error, setError] = useState("");

    const refreshAll = useCallback(async () => {
        if (!enabled) return;
        setLoading(true);
        setError("");
        try {
            const snapshot = await loadMonitorSnapshot();
            setAssets(snapshot.assets);
            setNodes(snapshot.nodes);
            setMovementRequests(snapshot.movementRequests);
            setAlerts([]);
            setActivity((current) => [makeRefreshActivity(), ...current].slice(0, 100));
        } catch (err) {
            setError(err?.message || "Failed to load monitor data.");
        } finally {
            setLoading(false);
        }
    }, [enabled]);

    const refreshNodes = useCallback(async () => {
        if (!enabled) return;
        try {
            setNodes(await loadNodesSnapshot());
        } catch (err) {
            console.warn("[Monitor] Failed to refresh node data:", err);
        }
    }, [enabled]);

    const refreshAssets = useCallback(async () => {
        if (!enabled) return;
        try {
            setAssets(await loadActiveAssetsSnapshot());
        } catch (err) {
            console.warn("[Monitor] Failed to reconcile asset data:", err);
        }
    }, [enabled]);

    useEffect(() => {
        if (!enabled) {
            setLoading(false);
            return;
        }
        refreshAll();
    }, [enabled, refreshAll]);

    useIntervalRefresh(enabled, refreshNodes, NODE_RECONCILIATION_INTERVAL_MS);
    useIntervalRefresh(enabled, refreshAssets, ASSET_RECONCILIATION_INTERVAL_MS);

    const summary = useMemo(() => buildMonitorSummary({
        assets, nodes, movementRequests, alerts,
    }), [assets, nodes, movementRequests, alerts]);

    return {
        assets, setAssets, nodes, setNodes, movementRequests, setMovementRequests,
        alerts, setAlerts, activity, setActivity, summary, loading, error,
        refreshAll, refreshNodes,
    };
}

function useIntervalRefresh(enabled, callback, intervalMs) {
    useEffect(() => {
        if (!enabled) return undefined;
        const intervalId = window.setInterval(callback, intervalMs);
        return () => window.clearInterval(intervalId);
    }, [enabled, callback, intervalMs]);
}

function makeRefreshActivity() {
    return {
        id: `refresh-${Date.now()}`,
        type: "system",
        message: "Monitor data refreshed.",
        createdAt: new Date().toISOString(),
    };
}
