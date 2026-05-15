/**
 * @file nodeHelpers.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-08

 * @Copyright (c) 2026
 */

export function getNodeLabel(node) {
    if (!node) {
        return "Unknown node";
    }

    return node.alias || node.room_name || node.device_id;
}