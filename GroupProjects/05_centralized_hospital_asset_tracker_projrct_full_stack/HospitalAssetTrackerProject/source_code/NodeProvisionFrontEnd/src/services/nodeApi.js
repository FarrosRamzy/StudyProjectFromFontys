/**
 * @file nodeApi.js
 * @author Farros Ramzy (you@domain.com)
 * @description Backend-compatible Node Registration API functions.
 * @version 1.0.0
 * @date 2026-05-11

 * @Copyright (c) 2026
 */

import { requestJson } from "./apiClient";

function jsonRequestOptions(method, payload) {
    return {
        method,
        body: JSON.stringify(payload),
    };
}

export async function getNodes() {
    return requestJson("/nodes");
}

// export async function enrollNode(payload) {
//     return requestJson("/nodes/enroll", {
//         method: "POST",
//         headers: {
//             "Content-Type": "application/json",
//         },
//         body: JSON.stringify(payload),
//     });
// }

export async function enrollNode(payload) {
    return requestJson("/nodes/enroll", jsonRequestOptions("POST", payload));
}

export async function assignNode(deviceId, payload) {
    // return requestJson(`/nodes/${encodeURIComponent(deviceId)}/assign`, {
    //     method: "POST",
    //     headers: {
    //         "Content-Type": "application/json",
    //     },
    //     body: JSON.stringify(payload),
    // });
    return requestJson(
        `/nodes/${encodeURIComponent(deviceId)}/assign`,
        jsonRequestOptions("POST", payload)
    );
}

export async function provisionNode(payload) {
    // return requestJson("/nodes/provision", {
    //     method: "POST",
    //     headers: {
    //         "Content-Type": "application/json",
    //     },
    //     body: JSON.stringify(payload),
    // });
    return requestJson("/nodes/provision", jsonRequestOptions("POST", payload));
}

export async function unassignNode(deviceId) {
    return requestJson(`/nodes/${encodeURIComponent(deviceId)}/unassign`, {
        method: "POST",
    });
}

export async function deleteNode(deviceId) {
    return requestJson(`/nodes/${encodeURIComponent(deviceId)}`, {
        method: "DELETE",
    });
}