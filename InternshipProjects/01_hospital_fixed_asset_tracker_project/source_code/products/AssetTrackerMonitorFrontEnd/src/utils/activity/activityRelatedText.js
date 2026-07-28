/**
 * @file activityRelatedText.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


export function getActivityRelatedText(item, assets, nodes) {
    const payload = item.payload || {};
    const payloadText = getPayloadText(payload);
    if (payloadText) return payloadText;

    const asset = assets.find((candidate) => candidate.tag_id === payload.tag_id);
    if (asset) return [asset.item_name, asset.tag_id, asset.last_room_name].filter(Boolean).join(" · ");

    const node = nodes.find((candidate) =>
        candidate.device_id === payload.device_id || candidate.device_id === payload.node_id
    );
    if (node) return [node.alias, node.device_id, node.room_name].filter(Boolean).join(" · ");
    return "-";
}

function getPayloadText(payload) {
    if (payload.item_name || payload.tag_id) {
        return [payload.item_name, payload.tag_id, payload.last_room_name || payload.room_name]
            .filter(Boolean).join(" · ");
    }
    if (payload.device_id || payload.node_id) {
        return [payload.alias, payload.device_id || payload.node_id, payload.room_name, payload.status]
            .filter(Boolean).join(" · ");
    }
    return "";
}
