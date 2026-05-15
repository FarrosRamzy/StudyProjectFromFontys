/**
 * @file assetSocketHandlers.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-12

 * @Copyright (c) 2026
 */

import {
    getMessageAsset,
    getMessageAssets,
    getMessageDeviceId,
    getMessageTagId,
    upsertAssetByTagId,
} from "./assetSocketUtils";

const ASSET_UPSERT_EVENTS = new Set([
    "asset_registered",
    "asset_updated",
    "asset_deregistered",
]);

export function handleAssetSocketMessage(message, handlers) {
    const {
        setAssets,
        setLatestScan,
        setTagId,
        setSelectedNodeId,
        setDeregisterNodeId,
        setSuccessMessage,
        setError,
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
            handleUnknownTag(message, {
                setSuccessMessage,
                setError,
            });
            return;

        case "inactive_asset_detected":
            handleInactiveAssetDetected(message, {
                setSuccessMessage,
                setError,
            });
            return;

        default:
            if (ASSET_UPSERT_EVENTS.has(message.type)) {
                handleAssetUpsert(message, setAssets);
            }
    }
}

function handleSnapshot(message, setAssets) {
    const snapshotAssets = getMessageAssets(message);

    if (Array.isArray(snapshotAssets)) {
        setAssets(snapshotAssets);
    }
}

function handleRegistrationScan(message, handlers) {
    const {
        setLatestScan,
        setTagId,
        setSelectedNodeId,
        setDeregisterNodeId,
        setSuccessMessage,
        setError,
    } = handlers;

    const scannedTagId = getMessageTagId(message);
    const scannedDeviceId = getMessageDeviceId(message);

    const scanEvent = {
        ...message,
        tag_id: scannedTagId,
        device_id: scannedDeviceId,
        received_at: Date.now(),
    };

    setLatestScan(scanEvent);
    setTagId(scannedTagId);

    if (scannedDeviceId) {
        setSelectedNodeId(scannedDeviceId);
        setDeregisterNodeId(scannedDeviceId);
    }

    setSuccessMessage(
        scannedTagId
            ? `Scanned tag ${scannedTagId} from registration node.`
            : "RFID scan received, but tag ID was empty."
    );

    setError("");
}

function handleAssetUpsert(message, setAssets) {
    const updatedAsset = getMessageAsset(message);

    if (!updatedAsset) {
        return;
    }

    setAssets((currentAssets) =>
        upsertAssetByTagId(currentAssets, updatedAsset)
    );
}

function handleAssetDeleted(message, setAssets) {
    const deletedTagId = getMessageTagId(message);

    if (!deletedTagId) {
        return;
    }

    setAssets((currentAssets) =>
        currentAssets.filter((asset) => asset.tag_id !== deletedTagId)
    );
}

function handleUnknownTag(message, handlers) {
    const { setSuccessMessage, setError } = handlers;
    const unknownTagId = getMessageTagId(message);

    setSuccessMessage("");
    setError(`Unknown RFID tag detected: ${unknownTagId || "unknown tag"}`);
}

function handleInactiveAssetDetected(message, handlers) {
    const { setSuccessMessage, setError } = handlers;

    const inactiveTagId = getMessageTagId(message);
    const inactiveAsset = getMessageAsset(message);

    setSuccessMessage("");
    setError(
        inactiveAsset?.item_name
            ? `Inactive asset detected: ${inactiveAsset.item_name} (${inactiveTagId})`
            : `Inactive asset detected: ${inactiveTagId || "unknown tag"}`
    );
}