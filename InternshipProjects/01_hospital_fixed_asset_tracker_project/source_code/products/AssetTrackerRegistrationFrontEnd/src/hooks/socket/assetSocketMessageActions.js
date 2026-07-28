/**
 * @file assetSocketMessageActions.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import {
    getMessageAsset,
    getMessageAssets,
    getMessageDeviceId,
    getMessageTagId,
    upsertAssetByTagId,
} from "./assetSocketUtils";

export function handleSnapshot(message, setAssets) {
    const snapshotAssets = getMessageAssets(message);

    if (Array.isArray(snapshotAssets)) {
        setAssets(snapshotAssets);
    }
}

export function handleRegistrationScan(message, handlers) {
    const scannedTagId = getMessageTagId(message);
    const scannedDeviceId = getMessageDeviceId(message);

    handlers.setLatestScan({
        ...message,
        tag_id: scannedTagId,
        device_id: scannedDeviceId,
        received_at: Date.now(),
    });
    handlers.setTagId(scannedTagId);

    if (scannedDeviceId) {
        handlers.setSelectedNodeId(scannedDeviceId);
        handlers.setDeregisterNodeId(scannedDeviceId);
    }

    handlers.setSuccessMessage(
        scannedTagId
            ? `Scanned tag ${scannedTagId} from registration node.`
            : "RFID scan received, but tag ID was empty."
    );
    handlers.setError("");
}

export function handleAssetUpsert(message, setAssets) {
    const updatedAsset = getMessageAsset(message);

    if (updatedAsset) {
        setAssets((currentAssets) => upsertAssetByTagId(currentAssets, updatedAsset));
    }
}

export function handleAssetDeleted(message, setAssets) {
    const deletedTagId = getMessageTagId(message);

    if (deletedTagId) {
        setAssets((currentAssets) => currentAssets.filter((asset) => asset.tag_id !== deletedTagId));
    }
}

export function handleUnknownTag(message, handlers) {
    const unknownTagId = getMessageTagId(message);

    handlers.setSuccessMessage("");
    handlers.setError(`Unknown RFID tag detected: ${unknownTagId || "unknown tag"}`);
}

export function handleInactiveAssetDetected(message, handlers) {
    const inactiveTagId = getMessageTagId(message);
    const inactiveAsset = getMessageAsset(message);

    handlers.setSuccessMessage("");
    handlers.setError(
        inactiveAsset?.item_name
            ? `Inactive asset detected: ${inactiveAsset.item_name} (${inactiveTagId})`
            : `Inactive asset detected: ${inactiveTagId || "unknown tag"}`
    );
}
