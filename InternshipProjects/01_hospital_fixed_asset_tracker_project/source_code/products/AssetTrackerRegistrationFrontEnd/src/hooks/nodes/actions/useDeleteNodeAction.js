/**
 * @file useDeleteNodeAction.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import { useState } from "react";
import { deleteNode } from "../../../services/nodeApi";
import { removeNodeById } from "../../../utils/nodeHelpers";
import { cleanDeviceId, confirmDelete } from "./nodeActionGuards";

export function useDeleteNodeAction({ setNodes, setError, setSuccessMessage }) {
    const [deletingNodeId, setDeletingNodeId] = useState("");

    async function handleDeleteNode(deviceId) {
        const cleanId = cleanDeviceId(deviceId);

        if (!cleanId) {
            setError("Cannot delete node because the device ID is missing.");
            return false;
        }

        if (!confirmDelete(cleanId)) {
            return false;
        }

        setDeletingNodeId(cleanId);
        setError("");
        setSuccessMessage("");

        try {
            await deleteNode(cleanId);
            setNodes((current) => removeNodeById(current, cleanId));
            setSuccessMessage("Node deleted successfully.");
            return true;
        } catch (err) {
            setError(err.message || "Failed to delete node.");
            return false;
        } finally {
            setDeletingNodeId("");
        }
    }

    return { deletingNodeId, handleDeleteNode };
}
