/**
 * @file NodeRoleBadge.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Role badge for registration/checkpoint node roles.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import {
    NODE_ROLE,
    NODE_ROLE_META,
} from "../../constants/nodeStatus";

import { formatRoleLabel } from "../../utils/textFormat";

export function NodeRoleBadge({ role }) {
    const normalizedRole = String(role || "")
        .trim()
        .toUpperCase();

    const meta =
        NODE_ROLE_META[normalizedRole] ||
        getFallbackRoleMeta(normalizedRole);

    return (
        <span
            className={`status-badge ${meta.tone}`}
            title={meta.description || meta.label}
        >
            {meta.label}
        </span>
    );
}

function getFallbackRoleMeta(role) {
    if (
        role === NODE_ROLE.REGISTRATION ||
        role === NODE_ROLE.REGISTRATION_DESK ||
        role.includes("REGISTRATION")
    ) {
        return {
            label: "Registration",
            tone: "info",
            description: "Node used for registration desk operations.",
        };
    }

    if (
        role === NODE_ROLE.CHECKPOINT ||
        role === NODE_ROLE.CHECKPOINT_NODE ||
        role.includes("CHECKPOINT")
    ) {
        return {
            label: "Checkpoint",
            tone: "success",
            description: "Node used for checkpoint asset detection.",
        };
    }

    return {
        label: formatRoleLabel(role || "Unknown"),
        tone: "neutral",
        description: "Unknown node role.",
    };
}
