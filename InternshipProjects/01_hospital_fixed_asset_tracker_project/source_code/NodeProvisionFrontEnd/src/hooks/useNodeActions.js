/**
 * @file useNodeAction.js
 * @author Farros Ramzy (you@domain.com)
 * @description Node action handlers for assigning, provisioning, unassigning, and deleting nodes.
 * @version 1.0.0
 * @date 2026-05-11

 * @Copyright (c) 2026
 */

import { useState } from "react";
import {
    assignNode,
    unassignNode,
    deleteNode,
    identifyNode,
} from "../services/nodeApi";
import {
    removeNodeById,
    upsertNode,
} from "../utils/nodeHelpers";

export function useNodeActions({
    setNodes,
    setError,
    setSuccessMessage,
    refreshData,
}) {
    const [assigning, setAssigning] = useState(false);
    const [unassigningNodeId, setUnassigningNodeId] = useState("");
    const [deletingNodeId, setDeletingNodeId] = useState("");
    const [identifyingNodeId, setIdentifyingNodeId] = useState("");

    async function handleAssignNode(deviceId, payload) {
        const cleanDeviceId = String(deviceId || "").trim();

        if (!cleanDeviceId) {
            setError("Cannot assign node because the device ID is missing.");
            return false;
        }

        setAssigning(true);
        setError("");
        setSuccessMessage("");

        try {
            const assignResult = await assignNode(cleanDeviceId, payload);

            const updatedNode = assignResult?.node || assignResult;

            if (updatedNode?.device_id) {
                setNodes((currentNodes) => upsertNode(currentNodes, updatedNode));
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

    async function handleUnassignNode(deviceId) {
        const cleanDeviceId = String(deviceId || "").trim();

        if (!cleanDeviceId) {
            setError("Cannot unassign node because the device ID is missing.");
            return false;
        }

        const confirmed = window.confirm(
            `Unassign node "${cleanDeviceId}"? The node will become available for assignment again.`
        );

        if (!confirmed) {
            return false;
        }

        setUnassigningNodeId(cleanDeviceId);
        setError("");
        setSuccessMessage("");

        try {
            const result = await unassignNode(cleanDeviceId);
            const updatedNode = result?.node || result;

            if (updatedNode?.device_id) {
                setNodes((currentNodes) => upsertNode(currentNodes, updatedNode));
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

    async function handleDeleteNode(deviceId) {
        const cleanDeviceId = String(deviceId || "").trim();

        if (!cleanDeviceId) {
            setError("Cannot delete node because the device ID is missing.");
            return false;
        }

        const confirmed = window.confirm(
            `Delete node "${cleanDeviceId}"? This action should only be used for removed or invalid devices.`
        );

        if (!confirmed) {
            return false;
        }

        setDeletingNodeId(cleanDeviceId);
        setError("");
        setSuccessMessage("");

        try {
            await deleteNode(cleanDeviceId);

            setNodes((currentNodes) => removeNodeById(currentNodes, cleanDeviceId));
            setSuccessMessage("Node deleted successfully.");
            return true;
        } catch (err) {
            setError(err.message || "Failed to delete node.");
            return false;
        } finally {
            setDeletingNodeId("");
        }
    }

    async function handleIdentifyNode(deviceId) {
        const cleanDeviceId = String(deviceId || "").trim();

        if (!cleanDeviceId) {
            setError("Cannot identify node because the device ID is missing.");
            return false;
        }

        setIdentifyingNodeId(cleanDeviceId);
        setError("");
        setSuccessMessage("");

        try {
            const result = await identifyNode(cleanDeviceId, {
                blink_count: 6,
                interval_ms: 150,
            });

            if (result?.message !== "blink_command_sent") {
                throw new Error(result?.message || "Failed to send blink command.");
            }

            setSuccessMessage(`Blink command sent to ${cleanDeviceId}.`);
            return true;
        } catch (err) {
            setError(err.message || "Failed to send blink command.");
            return false;
        } finally {
            setIdentifyingNodeId("");
        }
    }

    return {
        assigning,
        unassigningNodeId,
        deletingNodeId,
        identifyingNodeId,
        handleAssignNode,
        handleUnassignNode,
        handleDeleteNode,
        handleIdentifyNode,
    };
}