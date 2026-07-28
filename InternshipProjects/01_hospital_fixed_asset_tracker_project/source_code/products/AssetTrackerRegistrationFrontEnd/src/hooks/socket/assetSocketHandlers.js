/**
 * @file assetSocketHandlers.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-12

 * @Copyright (c) 2026
 */


import {
    ASSET_UPSERT_EVENTS,
    MOVEMENT_REQUEST_CHANGED_EVENTS,
} from "./assetSocketEventSets";
import {
    handleAssetDeleted,
    handleAssetUpsert,
    handleInactiveAssetDetected,
    handleRegistrationScan,
    handleSnapshot,
    handleUnknownTag,
} from "./assetSocketMessageActions";

export function handleAssetSocketMessage(message, handlers) {
    const {
        setAssets,
        setLatestScan,
        setTagId,
        setSelectedNodeId,
        setDeregisterNodeId,
        setSuccessMessage,
        setError,
        onMovementRequestChanged,
    } = handlers;

    switch (message.type) {
        case "snapshot":
            handleSnapshot(message, setAssets);
            return;
        case "asset_registration_scan":
            handleRegistrationScan(message, {
                setLatestScan,
                setTagId,
                setSelectedNodeId,
                setDeregisterNodeId,
                setSuccessMessage,
                setError,
            });
            return;
        case "asset_deleted":
            handleAssetDeleted(message, setAssets);
            return;
        case "unknown_tag":
            handleUnknownTag(message, { setSuccessMessage, setError });
            return;
        case "inactive_asset_detected":
            handleInactiveAssetDetected(message, { setSuccessMessage, setError });
            return;
        default:
            handleDefaultAssetEvent(message, {
                setAssets,
                onMovementRequestChanged,
            });
    }
}

function handleDefaultAssetEvent(message, { setAssets, onMovementRequestChanged }) {
    if (ASSET_UPSERT_EVENTS.has(message.type)) {
        handleAssetUpsert(message, setAssets);
    }

    if (MOVEMENT_REQUEST_CHANGED_EVENTS.has(message.type)) {
        onMovementRequestChanged?.(message);
    }
}
