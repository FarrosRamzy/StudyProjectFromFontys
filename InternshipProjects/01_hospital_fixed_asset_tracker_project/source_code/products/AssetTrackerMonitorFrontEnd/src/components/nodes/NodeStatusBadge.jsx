/**
 * @file NodeStatusBadge.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Status badge for node online/offline/disabled states.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import {
    NODE_STATUS,
    NODE_STATUS_META,
} from "../../constants/nodeStatus";

import { formatStatusLabel } from "../../utils/textFormat";

export function NodeStatusBadge({ status, isProvisioned = true }) {
    const normalizedStatus = getDisplayStatus(status, isProvisioned);

    const meta =
        NODE_STATUS_META[normalizedStatus] ||
        NODE_STATUS_META[NODE_STATUS.UNKNOWN] ||
        {
            label: formatStatusLabel(normalizedStatus || "unknown"),
            tone: "warning",
        };

    return (
        <span
            className={`status-badge ${meta.tone}`}
            title={meta.description || meta.label}
        >
            {meta.label}
        </span>
    );
}

function getDisplayStatus(status, isProvisioned) {
    const normalizedStatus = String(status || NODE_STATUS.UNKNOWN)
        .trim()
        .toUpperCase();

    if (normalizedStatus === NODE_STATUS.DISABLED) {
        return NODE_STATUS.DISABLED;
    }

    if (normalizedStatus === NODE_STATUS.OFFLINE) {
        return NODE_STATUS.OFFLINE;
    }

    if (normalizedStatus === NODE_STATUS.ONLINE) {
        return NODE_STATUS.ONLINE;
    }

    if (!isProvisioned) {
        return NODE_STATUS.UNKNOWN;
    }

    if (normalizedStatus === "DISCOVERED") {
        return NODE_STATUS.UNKNOWN;
    }

    return normalizedStatus;
}
