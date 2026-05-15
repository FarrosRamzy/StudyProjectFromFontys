/**
 * @file assetApi.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-08

 * @Copyright (c) 2026
 */

import { requestJson } from "./apiClient";

export async function getAssets() {
    return requestJson("/assets");
}

export async function registerAsset(payload) {
    return requestJson("/assets/register", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(payload),
    });
}

export async function deregisterAsset(payload) {
    return requestJson("/assets/deregister", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(payload),
    });
}

export async function deleteAsset(tagId) {
    return requestJson(`/assets/${encodeURIComponent(tagId)}`, {
        method: "DELETE",
    });
}