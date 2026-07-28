/**
 * @file assetApi.js
 * @author Farros Ramzy (you@domain.com)
 * @description Asset and movement request API helpers.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { apiRequest } from "./apiClient";

export async function getAssets() {
    const data = await apiRequest("/assets");

    if (Array.isArray(data)) {
        return data;
    }

    return data?.assets || data?.items || [];
}

export async function getAssetByTagId(tagId) {
    return apiRequest(`/assets/${encodeURIComponent(tagId)}`);
}

export async function createMovementRequest(payload) {
    return apiRequest("/assets/movement/request", {
        method: "POST",
        body: JSON.stringify({
            tag_id: payload.tag_id,
            destination_room_name: payload.destination_room_name,
            destination_node_id: payload.destination_node_id || "",
            reason: payload.reason || "",
        }),
    });
}

export async function cancelMovementRequest(movementRequestId) {
    return apiRequest("/assets/movement/cancel", {
        method: "POST",
        body: JSON.stringify({
            movement_request_id: movementRequestId,
        }),
    });
}

export async function getMovementRequests(status = "") {
    const query = status ? `?status=${encodeURIComponent(status)}` : "";
    const data = await apiRequest(`/assets/movement/requests${query}`);

    if (Array.isArray(data)) {
        return data;
    }

    return data?.movement_requests || data?.requests || data?.items || [];
}

export async function getPendingMovementRequests() {
    return getMovementRequests("pending");
}

export async function getAssetEvents(tagId) {
    const query = tagId ? `?tag_id=${encodeURIComponent(tagId)}` : "";
    const data = await apiRequest(`/assets/events${query}`);

    if (Array.isArray(data)) {
        return data;
    }

    return data?.events || data?.items || [];
}

export function normalizeAsset(asset) {
    if (!asset) {
        return null;
    }

    return {
        ...asset,
        tag_id: asset.tag_id || asset.tagId || "",
        item_name: asset.item_name || asset.asset_name || asset.name || "",
        status: asset.status || "",
        flow_status: asset.flow_status || "",
        last_room_name: asset.last_room_name || "",
        assigned_room_name: asset.assigned_room_name || "",
        expected_room_name: asset.expected_room_name || "",
        movement_note: asset.movement_note || "",
    };
}

export function upsertAssetInList(assets, incomingAsset) {
    const normalizedAsset = normalizeAsset(incomingAsset);

    if (!normalizedAsset?.tag_id) {
        return assets;
    }

    const exists = assets.some((asset) => asset.tag_id === normalizedAsset.tag_id);

    if (!exists) {
        return [normalizedAsset, ...assets];
    }

    return assets.map((asset) =>
        asset.tag_id === normalizedAsset.tag_id
            ? {
                ...asset,
                ...normalizedAsset,
            }
            : asset
    );
}

export function removeAssetFromList(
    assets,
    assetOrTagId
) {
    const tagId =
        typeof assetOrTagId === "string"
            ? assetOrTagId
            : assetOrTagId?.tag_id ||
              assetOrTagId?.tagId ||
              "";

    const normalizedTagId = String(tagId || "").trim();

    if (!normalizedTagId) {
        return assets;
    }

    return assets.filter(
        (asset) =>
            String(asset?.tag_id || "").trim() !==
            normalizedTagId
    );
}
