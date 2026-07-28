/**
 * @file useUnassignNodeAction.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import { useState } from "react";
import { unassignNode } from "../../../services/nodeApi";
import { upsertNode } from "../../../utils/nodeHelpers";
import {
    formatNodeBlockerMessage,
    isNodeOperationBlocked,
} from "../../../utils/nodes/nodeBlockerMessages";
import { cleanDeviceId, confirmUnassign } from "./nodeActionGuards";

export function useUnassignNodeAction({ setNodes, setError, setSuccessMessage, refreshData }) {
    const [unassigningNodeId, setUnassigningNodeId] = useState("");

    async function handleUnassignNode(deviceId) {
        const cleanId = cleanDeviceId(deviceId);

        if (!cleanId) {
            setError("Cannot unassign node because the device ID is missing.");
            return false;
        }

        if (!confirmUnassign(cleanId)) {
            return false;
        }

        setUnassigningNodeId(cleanId);
        setError("");
        setSuccessMessage("");

        try {
            const result = await unassignNode(cleanId);

            if (isNodeOperationBlocked(result)) {
                setError(formatNodeBlockerMessage(result));
                return false;
            }

            if (result?.message && result.message !== "node_unassigned") {
                setError(result.reason || result.message || "Failed to unassign node.");
                return false;
            }

            if (result?.node?.device_id) {
                setNodes((current) => upsertNode(current, result.node));
            } else {
                await refreshData();
            }

            setSuccessMessage("Node unassigned successfully.");
            return true;
        } catch (err) {
            setError(err.message || "Failed to unassign node.");
            return false;
        } finally {
            setUnassigningNodeId("");
        }
    }

    return { unassigningNodeId, handleUnassignNode };
}
