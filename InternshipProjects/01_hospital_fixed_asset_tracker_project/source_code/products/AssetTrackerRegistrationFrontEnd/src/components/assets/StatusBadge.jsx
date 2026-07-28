/**
 * @file StatusBadge.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-07

 * @Copyright (c) 2026
 */


function getBadgeTone(status) {
    const normalized = String(status || "").toLowerCase();

    if (
        [
            "active",
            "available",
            "completed",
            "online",
            "provisioned",
        ].includes(normalized)
    ) {
        return "success";
    }

    if (
        [
            "pending",
            "pending_placement",
            "movement_requested",
            "offline",
        ].includes(normalized)
    ) {
        return "warning";
    }

    if (
        [
            "in_transit",
            "wrong_location",
            "unauthorized_movement",
            "deregistered",
            "rejected",
            "disabled",
            "error",
        ].includes(normalized)
    ) {
        return "danger";
    }

    if (["approved"].includes(normalized)) {
        return "info";
    }

    return "neutral";
}

function formatStatusLabel(status) {
    return String(status || "unknown")
        .replaceAll("_", " ")
        .replace(/\b\w/g, (character) => character.toUpperCase());
}

export default function StatusBadge({ status }) {
    const cleanStatus = String(status || "unknown").trim();
    const tone = getBadgeTone(cleanStatus);

    return (
        <span className={`status-badge ${tone}`}>
            {formatStatusLabel(cleanStatus)}
        </span>
    );
}
