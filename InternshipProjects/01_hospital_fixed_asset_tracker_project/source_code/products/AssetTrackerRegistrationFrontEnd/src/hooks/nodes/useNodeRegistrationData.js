/**
 * @file useNodeRegistrationData.js
 * @author Farros Ramzy (you@domain.com)
 * @description Loads and stores node registration data.
 * @version 2.0.0
 * @date 2026-05-11

 * @Copyright (c) 2026
 */


import { useCallback, useEffect, useState } from "react";
import { getNodes } from "../../services/nodeApi";
import { normalizeNodes } from "../../utils/nodeHelpers";

export function useNodeRegistrationData() {
    const [nodes, setNodes] = useState([]);
    const [loading, setLoading] = useState(false);

    const [error, setError] = useState("");
    const [successMessage, setSuccessMessage] = useState("");

    const refreshData = useCallback(async () => {
        setLoading(true);
        setError("");

        try {
            const nodeData = await getNodes();

            const normalizedNodes = normalizeNodes(
                Array.isArray(nodeData) ? nodeData : nodeData?.nodes
            );

            setNodes(normalizedNodes);
        } catch (err) {
            setError(err.message || "Failed to load node registration data.");
        } finally {
            setLoading(false);
        }
    }, []);

    useEffect(() => {
        refreshData();
    }, [refreshData]);

    return {
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