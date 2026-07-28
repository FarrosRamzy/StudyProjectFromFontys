/**
 * @file useAssignNodeAction.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import { useState } from "react";
import { assignNode } from "../../../services/nodeApi";
import { upsertNode } from "../../../utils/nodeHelpers";
import {
    formatNodeBlockerMessage,
    isNodeOperationBlocked,
} from "../../../utils/nodes/nodeBlockerMessages";
import { cleanDeviceId } from "./nodeActionGuards";

export function useAssignNodeAction({ setNodes, setError, setSuccessMessage, refreshData }) {
    const [assigning, setAssigning] = useState(false);

    async function handleAssignNode(deviceId, payload) {
        const cleanId = cleanDeviceId(deviceId);

        if (!cleanId) {
            setError("Cannot assign node because the device ID is missing.");
            return false;
        }

        setAssigning(true);
        setError("");
        setSuccessMessage("");

        try {
            const result = await assignNode(cleanId, payload);

            if (isNodeOperationBlocked(result)) {
                setError(formatNodeBlockerMessage(result));
                return false;
            }

            if (result?.message && result.message !== "node_assigned") {
                setError(result.reason || result.message || "Failed to assign node.");
                return false;
            }

            if (result?.node?.device_id) {
                setNodes((current) => upsertNode(current, result.node));
            } else {
                await refreshData();
            }

            setSuccessMessage("Node assigned successfully.");
            return true;
        } catch (err) {
            setError(err.message || "Failed to assign node.");
            return false;
        } finally {
            setAssigning(false);
        }
    }

    return { assigning, handleAssignNode };
}
