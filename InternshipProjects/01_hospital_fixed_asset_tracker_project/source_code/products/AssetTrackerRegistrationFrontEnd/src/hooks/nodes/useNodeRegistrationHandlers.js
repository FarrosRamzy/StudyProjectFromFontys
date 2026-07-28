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
} from "../../utils/nodeHelpers";
import { getHospitalNameFromSettings } from "../../utils/settings/mqttSettingsFormatters";
import {
    confirmDangerousNodeReassignment,
    isDangerousNodeReassignment,
} from "./nodeRegistrationHandlerHelpers";

export function useNodeRegistrationHandlers(options) {
    const context = buildHandlerContext(options);

    function handleSelectNode(node) {
        const selectedNodeId = getNodeIdentity(context.selectedNode);
        const clickedNodeId = getNodeIdentity(node);

        if (selectedNodeId && selectedNodeId === clickedNodeId) {
            context.resetForm();
            clearMessages(context);
            return;
        }

        context.setSelectedNode(node);
        context.fillFormFromNode(node);
        clearMessages(context);
    }

    function handleCancelForm() {
        context.resetForm();
        clearMessages(context);
    }

    async function handleAssignSubmit(event) {
        event.preventDefault();
        const formValues = getFormValues(context);
        const validation = validateNodeAssignmentForm(formValues);

        if (!validation.valid) {
            context.setError(validation.message);
            return;
        }

        if (shouldConfirmReassignment(context, formValues)) {
            if (!confirmDangerousNodeReassignment()) {
                return;
            }
        }

        const deviceId = getNodeIdentity(context.selectedNode);
        const payload = buildNodeAssignmentPayload(formValues);
        const succeeded = await context.handleAssignNode(deviceId, payload);

        if (succeeded) {
            context.resetForm();
        }
    }

    async function handleUnassignSelectedNode() {
        await runSelectedNodeAction(context, {
            missingMessage: "Please select a node before unassigning.",
            idMessage: "Cannot unassign node because the device ID is missing.",
            action: context.handleUnassignNode,
        });
    }

    async function handleDeleteSelectedNode() {
        await runSelectedNodeAction(context, {
            missingMessage: "Please select a node before deleting.",
            idMessage: "Cannot delete node because the device ID is missing.",
            action: context.handleDeleteNode,
        });
    }

    return {
        handleSelectNode,
        handleCancelForm,
        handleAssignSubmit,
        handleUnassignSelectedNode,
        handleDeleteSelectedNode,
    };
}

function buildHandlerContext(options) {
    return {
        ...options,
        mqttSettings: options.mqttSettings || {},
    };
}

function getFormValues(context) {
    const settings = context.mqttSettings;

    return {
        selectedNode: context.selectedNode,
        alias: context.alias,
        role: context.role,
        hospitalName: getHospitalNameFromSettings(settings),
        hospitalId: settings.hospital_id || "",
        roomName: context.roomName,
        mqttHost: settings.broker_host || "",
        mqttPort: settings.broker_port || 1883,
    };
}

function shouldConfirmReassignment(context, formValues) {
    return isDangerousNodeReassignment({
        selectedNode: context.selectedNode,
        role: context.role,
        hospitalName: formValues.hospitalName,
        roomName: context.roomName,
    });
}

function clearMessages(context) {
    context.setError("");
    context.setSuccessMessage("");
}

async function runSelectedNodeAction(context, config) {
    if (!context.selectedNode) {
        context.setError(config.missingMessage);
        return;
    }

    const deviceId = getNodeIdentity(context.selectedNode);

    if (!deviceId) {
        context.setError(config.idMessage);
        return;
    }

    const succeeded = await config.action(deviceId);

    if (succeeded) {
        context.resetForm();
    }
}
