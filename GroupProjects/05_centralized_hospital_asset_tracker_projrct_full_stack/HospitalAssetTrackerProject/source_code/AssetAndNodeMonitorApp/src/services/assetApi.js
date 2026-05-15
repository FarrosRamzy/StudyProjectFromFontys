/**
 * @file assetApi.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-12

 * @Copyright (c) 2026
 */

import { apiRequest } from "./apiClient";

export function getAssets() {
    return apiRequest("/assets");
}

export function getAssetEvents() {
    return apiRequest("/events");
}