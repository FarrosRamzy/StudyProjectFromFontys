/**
 * @file assetSocketUtils.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-12

 * @Copyright (c) 2026
 */

export function upsertAssetByTagId(currentAssets, updatedAsset) {
    if (!updatedAsset?.tag_id) {
        return currentAssets;
    }

    const exists = currentAssets.some(
        (asset) => asset.tag_id === updatedAsset.tag_id
    );

    if (!exists) {
        return [updatedAsset, ...currentAssets];
    }

    return currentAssets.map((asset) =>
        asset.tag_id === updatedAsset.tag_id ? updatedAsset : asset
    );
}

export function getMessageAsset(message) {
    return message?.asset || message?.payload?.asset || message?.data?.asset || null;
}

export function getMessageAssets(message) {
    return message?.assets || message?.payload?.assets || message?.data?.assets || [];
}

export function getMessageTagId(message) {
    return String(
        message?.tag_id ||
        message?.payload?.tag_id ||
        message?.data?.tag_id ||
        ""
    ).trim();
}

export function getMessageDeviceId(message) {
    return String(
        message?.device_id ||
        message?.payload?.device_id ||
        message?.data?.device_id ||
        ""
    ).trim();
}