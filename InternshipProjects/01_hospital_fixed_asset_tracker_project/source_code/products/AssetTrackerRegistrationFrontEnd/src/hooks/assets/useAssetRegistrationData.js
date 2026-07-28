/**
 * @file useAssetRegistrationData.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-07

 * @Copyright (c) 2026
 */


import { useCallback, useEffect, useState } from "react";
import { getAssets } from "../../services/assetApi";
import { getNodes } from "../../services/nodeApi";

export function useAssetRegistrationData() {
    const [assets, setAssets] = useState([]);
    const [nodes, setNodes] = useState([]);

    const [loading, setLoading] = useState(false);
    const [error, setError] = useState("");
    const [successMessage, setSuccessMessage] = useState("");

    const refreshData = useCallback(async () => {
        setLoading(true);
        setError("");

        try {
            const [assetData, nodeData] = await Promise.all([
                getAssets(),
                getNodes(),
            ]);

            const normalizedAssets = Array.isArray(assetData)
                ? assetData
                : assetData?.assets ?? [];

            const normalizedNodes = Array.isArray(nodeData)
                ? nodeData
                : nodeData?.nodes ?? [];

            setAssets(normalizedAssets);
            setNodes(normalizedNodes);
        } catch (err) {
            setError(err.message || "Failed to load asset registration data.");
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
        loading,
        error,
        setError,
        successMessage,
        setSuccessMessage,
        refreshData,
    };
}