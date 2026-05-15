/**
 * @file useMonitorData.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-12

 * @Copyright (c) 2026
 */

import { useCallback, useEffect, useState } from "react";
import { getAssets } from "../services/assetApi";
import { getNodes } from "../services/nodeApi";

function normalizeArray(data, key) {
    if (Array.isArray(data)) {
        return data;
    }

    if (Array.isArray(data?.[key])) {
        return data[key];
    }

    return [];
}

export function useMonitorData() {
    const [assets, setAssets] = useState([]);
    const [nodes, setNodes] = useState([]);
    const [alerts, setAlerts] = useState([]);
    const [activity, setActivity] = useState([]);

    const [loading, setLoading] = useState(true);
    const [error, setError] = useState("");

    const refreshData = useCallback(async () => {
        setLoading(true);
        setError("");

        try {
            const [assetData, nodeData] = await Promise.all([
                getAssets(),
                getNodes(),
            ]);

            setAssets(normalizeArray(assetData, "assets"));
            setNodes(normalizeArray(nodeData, "nodes"));
        } catch (err) {
            setError(err.message || "Failed to load monitor data.");
        } finally {
            setLoading(false);
        }
    }, []);

    useEffect(() => {
        refreshData();
    }, [refreshData]);

    return {
        assets,
        setAssets,
        nodes,
        setNodes,
        alerts,
        setAlerts,
        activity,
        setActivity,
        loading,
        error,
        setError,
        refreshData,
    };
}