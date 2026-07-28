/**
 * @file useAssetMovementActions.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { useState } from "react";
import { cancelMovementRequest, createMovementRequest } from "../../services/assetApi";
import { getMovementRequestId, getPendingMovementRequestForAsset } from "../../utils/assets/movementRequestLookup";

export function useAssetMovementActions({ movementRequests = [], onRefresh } = {}) {
    const [selectedAsset, setSelectedAsset] = useState(null);
    const [requestError, setRequestError] = useState("");
    const [requestSuccess, setRequestSuccess] = useState("");
    const [submittingRequest, setSubmittingRequest] = useState(false);
    const [cancelingRequestId, setCancelingRequestId] = useState(null);

    async function submitMovementRequest(payload) {
        setSubmittingRequest(true);
        clearMessages();
        try {
            const result = await createMovementRequest(payload);
            if (result?.message === "movement_request_already_exists") {
                setSelectedAsset(null);
                setRequestError("This asset already has a pending or approved movement request.");
                await onRefresh?.();
                return;
            }
            if (result?.message && result.message !== "movement_requested") {
                setRequestError(result.reason || result.message || "Failed to submit movement request.");
                return;
            }
            setRequestSuccess("Movement request submitted successfully.");
            setSelectedAsset(null);
            await onRefresh?.();
        } catch (error) {
            setRequestError(error?.message || "Failed to submit movement request.");
        } finally {
            setSubmittingRequest(false);
        }
    }

    async function cancelAssetMovementRequest(asset) {
        const request = getPendingMovementRequestForAsset(asset, movementRequests);
        if (!request) return setRequestError("No pending movement request was found for this asset.");
        const requestId = getMovementRequestId(request);
        if (!window.confirm(`Cancel movement request for "${asset.item_name || asset.tag_id}"?`)) return;
        setCancelingRequestId(requestId);
        clearMessages();
        try {
            const result = await cancelMovementRequest(requestId);
            if (result?.message !== "movement_cancelled") {
                setRequestError(result?.reason || result?.message || "Failed to cancel movement request.");
                return;
            }
            setRequestSuccess("Movement request cancelled successfully.");
            await onRefresh?.();
        } catch (error) {
            setRequestError(error?.message || "Failed to cancel movement request.");
        } finally {
            setCancelingRequestId(null);
        }
    }

    function clearMessages() {
        setRequestError("");
        setRequestSuccess("");
    }

    return {
        selectedAsset, setSelectedAsset, requestError, requestSuccess,
        submittingRequest, cancelingRequestId, clearMessages,
        submitMovementRequest, cancelAssetMovementRequest,
    };
}
