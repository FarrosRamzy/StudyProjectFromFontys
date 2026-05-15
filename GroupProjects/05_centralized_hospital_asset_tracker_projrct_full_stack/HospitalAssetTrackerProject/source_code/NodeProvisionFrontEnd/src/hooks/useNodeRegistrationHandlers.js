/**
 * @file useNodeRegistrationHandlers.js
 * @author Farros Ramzy (you@domain.com)
 * @description Submit and selected-node action handlers for the Node Registration page.
 * @version 1.1.0
 * @date 2026-05-11
 *
 * @Copyright (c) 2026
 */

import {
    buildNodeAssignmentPayload,
    getNodeIdentity,
    validateNodeAssignmentForm,
} from "../utils/nodeHelpers";

export function useNodeRegistrationHandlers({
    selectedNode,
    setSelectedNode,
    fillFormFromNode,

    alias,
    role,
    hospitalName,
    roomName,
    mqttHost,
    mqttPort,
    resetForm,

    setError,
    setSuccessMessage,

    handleAssignNode,
    handleUnassignNode,
    handleDeleteNode,
}) {
    function handleSelectNode(node) {
        const selectedNodeId = getNodeIdentity(selectedNode);
        const clickedNodeId = getNodeIdentity(node);

        if (selectedNodeId && selectedNodeId === clickedNodeId) {
            resetForm();
            setError("");
            setSuccessMessage("");
            return;
        }

        setSelectedNode(node);
        fillFormFromNode(node);
        setError("");
        setSuccessMessage("");
    }

    function handleCancelForm() {
        resetForm();
        setError("");
        setSuccessMessage("");
    }

    async function handleAssignSubmit(event) {
        event.preventDefault();

        const validation = validNodeAssignmentForm({
            selectedNode,
            alias,
            role,
            hospitalName,
            roomName,
            mqttHost,
            mqttPort,
        });

        if (!validation.valid) {
            setError(validation.message);
            // setError(
            //     "Please select a node and complete all required fields. Checkpoint nodes require a room name."
            // );
            return;
        }

        const deviceId = getNodeIdentity(selectedNode);

        const payload = buildNodeAssignmentPayload({
            alias,
            role,
            hospitalName,
            roomName,
            mqttHost,
            mqttPort,
        });

        // await handleAssignNode(deviceId, payload);
        // resetForm();
        const succeeded = await handleAssignNode(deviceId, payload);

        if (succeeded) {
            resetForm();
        }
    }
    
    async function handleUnassignSelectedNode() {
        if (!selectedNode) {
            setError("Please select a node before unassigning.");
            return;
        }
        
        const deviceId = getNodeIdentity(selectedNode);
        
        if (!deviceId) {
            setError("Cannot unassign node because the device ID is missing.");
            return;
        }
        
        // await handleUnassignNode(deviceId);
        // resetForm();
        const succeeded = await handleUnassignNode(deviceId);
    
        if (succeeded) {
            resetForm();
        }
    }

    async function handleDeleteSelectedNode() {
        if (!selectedNode) {
            setError("Please select a node before deleting.");
            return;
        }

        const deviceId = getNodeIdentity(selectedNode);

        if (!deviceId) {
            setError("Cannot delete node because the device ID is missing.");
            return;
        }

        // await handleDeleteNode(deviceId);
        // resetForm();
        const succeeded = await handleDeleteNode(deviceId);

        if (succeeded) {
            resetForm();
        }
    }

    return {
        handleSelectNode,
        handleCancelForm,
        handleAssignSubmit,
        handleUnassignSelectedNode,
        handleDeleteSelectedNode,
    };
}