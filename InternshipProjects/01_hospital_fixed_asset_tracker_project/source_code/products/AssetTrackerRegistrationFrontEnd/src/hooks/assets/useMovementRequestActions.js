/**
 * @file useMovementRequestActions.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { useCallback, useEffect, useState } from "react";
import {
    approveAssetMovement,
    getMovementRequests,
    rejectAssetMovement,
} from "../../services/assetApi";
import {
    normalizeMovementRequests,
    removeMovementRequest,
    upsertAssetByTagId,
    validateMovementAction,
} from "./movement/movementRequestHelpers";

export function useMovementRequestActions({
    registrationNodeId,
    registrationNodes,
    setAssets,
    setError,
    setSuccessMessage,
}) {
    const [movementRequests, setMovementRequests] = useState([]);
    const [loadingMovementRequests, setLoadingMovementRequests] = useState(false);
    const [actingMovementRequestId, setActingMovementRequestId] = useState(null);

    const refreshMovementRequests = useCallback(async () => {
        setLoadingMovementRequests(true);
        setError("");

        try {
            const result = await getMovementRequests("pending");
            setMovementRequests(normalizeMovementRequests(result));
        } catch (err) {
            setError(err.message || "Failed to load movement requests.");
        } finally {
            setLoadingMovementRequests(false);
        }
    }, [setError]);

    useEffect(() => {
        refreshMovementRequests();
    }, [refreshMovementRequests]);

    async function handleApproveMovementRequest(request) {
        const valid = validateMovementAction({
            request,
            registrationNodeId,
            registrationNodes,
            setError,
            actionName: "approving",
        });

        if (!valid || !window.confirm(getApproveMessage(request))) {
            return;
        }

        await submitMovementDecision({
            request,
            submitter: approveAssetMovement,
            successMessage: "Movement request approved.",
        });
    }

    async function handleRejectMovementRequest(request) {
        const valid = validateMovementAction({
            request,
            registrationNodeId,
            registrationNodes,
            setError,
            actionName: "rejecting",
        });

        if (!valid || !window.confirm(`Reject movement request for "${request.item_name || request.tag_id}"?`)) {
            return;
        }

        await submitMovementDecision({
            request,
            submitter: rejectAssetMovement,
            successMessage: "Movement request rejected.",
        });
    }

    async function submitMovementDecision({ request, submitter, successMessage }) {
        setActingMovementRequestId(request.id);
        setError("");
        setSuccessMessage("");

        try {
            const result = await submitter({
                movement_request_id: request.id,
                registration_node_id: registrationNodeId,
            });

            if (result.asset) {
                setAssets((currentAssets) => upsertAssetByTagId(currentAssets, result.asset));
            }

            setMovementRequests((currentRequests) => removeMovementRequest(currentRequests, request.id));
            setSuccessMessage(successMessage);
        } catch (err) {
            setError(err.message || "Failed to update movement request.");
        } finally {
            setActingMovementRequestId(null);
        }
    }

    return {
        movementRequests,
        loadingMovementRequests,
        actingMovementRequestId,
        refreshMovementRequests,
        handleApproveMovementRequest,
        handleRejectMovementRequest,
    };
}

function getApproveMessage(request) {
    return `Approve movement for "${request.item_name || request.tag_id}"?\n\nDestination: ${request.destination_room_name || "-"}`;
}
