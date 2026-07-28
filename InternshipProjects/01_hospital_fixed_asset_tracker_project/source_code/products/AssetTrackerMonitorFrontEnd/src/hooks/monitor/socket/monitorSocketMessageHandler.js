/**
 * @file monitorSocketMessageHandler.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { normalizeAsset, removeAssetFromList, upsertAssetInList } from "../../../services/assetApi";
import { normalizeNode, upsertNodeInList } from "../../../services/nodeApi";
import { ALERT_EVENTS, ASSET_REMOVE_EVENTS, ASSET_UPSERT_EVENTS, MOVEMENT_REQUEST_UPSERT_EVENTS, NODE_UPSERT_EVENTS } from "./socketEventSets";
import { addSocketActivity, getEventType, getPayload } from "./socketActivity";
import { getRequestPayload, upsertMovementRequestInList } from "./socketMovementRequests";
import { makeSocketAlert } from "./socketAlerts";

export function createMonitorMessageHandler(setters) {
    return function handleMessage(message) {
        const type = getEventType(message);
        const payload = getPayload(message);
        if (!type) return;
        if (type === "snapshot") return handleSnapshot(message, payload, setters);
        if (MOVEMENT_REQUEST_UPSERT_EVENTS.has(type)) return handleMovement(type, payload, setters);
        if (ASSET_REMOVE_EVENTS.has(type)) return handleAssetRemove(type, message, payload, setters);
        if (ASSET_UPSERT_EVENTS.has(type)) return handleAssetUpsert(type, payload, setters);
        if (NODE_UPSERT_EVENTS.has(type)) return handleNodeUpsert(type, message, payload, setters);
        if (ALERT_EVENTS.has(type)) return handleAlert(type, payload, setters);
        addSocketActivity(setters.setActivity, type, payload);
    };
}

function handleSnapshot(message, payload, { setAssets, setNodes }) {
    const assets = Array.isArray(message.assets) ? message.assets : payload.assets || [];
    const nodes = Array.isArray(message.nodes) ? message.nodes : payload.nodes || [];
    setAssets?.(assets.map(normalizeAsset).filter(Boolean));
    setNodes?.(nodes.map(normalizeNode).filter(Boolean));
}

function handleMovement(type, payload, setters) {
    const requestPayload = getRequestPayload(type, payload);
    setters.setMovementRequests?.((current) => upsertMovementRequestInList(current, requestPayload));
    const normalizedAsset = payload.asset ? normalizeAsset(payload.asset) : null;
    if (normalizedAsset) setters.setAssets?.((current) => upsertAssetInList(current, normalizedAsset));
    addSocketActivity(setters.setActivity, type, requestPayload);
}

function handleAssetRemove(type, message, payload, setters) {
    const assetPayload = message?.asset || payload?.asset || payload;
    const tagId = assetPayload?.tag_id || assetPayload?.tagId || message?.tag_id || payload?.tag_id || "";
    if (tagId) {
        setters.setAssets?.((current) => removeAssetFromList(current, tagId));
        setters.setMovementRequests?.((current) => current.filter((request) => String(request?.tag_id || "").trim() !== String(tagId).trim()));
    }
    addSocketActivity(setters.setActivity, type, assetPayload);
}

function handleAssetUpsert(type, payload, setters) {
    const assetPayload = payload.asset || payload;
    const normalizedAsset = normalizeAsset(assetPayload);
    if (normalizedAsset) setters.setAssets?.((current) => upsertAssetInList(current, normalizedAsset));
    addSocketActivity(setters.setActivity, type, normalizedAsset || assetPayload);
}

function handleNodeUpsert(type, message, payload, setters) {
    const normalizedNode = normalizeNode(payload.node || message.node || payload);
    if (normalizedNode) setters.setNodes?.((current) => upsertNodeInList(current, normalizedNode));
    addSocketActivity(setters.setActivity, type, normalizedNode || payload);
}

function handleAlert(type, payload, setters) {
    const alert = makeSocketAlert(type, payload);
    setters.setAlerts?.((current) => [alert, ...current].slice(0, 100));
    addSocketActivity(setters.setActivity, type, alert.payload);
}
