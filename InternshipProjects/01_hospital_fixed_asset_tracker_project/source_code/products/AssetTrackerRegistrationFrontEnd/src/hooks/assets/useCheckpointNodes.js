/**
 * @file useCheckpointNodes.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { useMemo } from "react";

function normalizeText(value) {
    return String(value || "").trim().toUpperCase();
}

export function useCheckpointNodes(nodes) {
    return useMemo(() => {
        return nodes.filter((node) => {
            const role = normalizeText(node.role);
            const status = normalizeText(node.status);

            const isCheckpoint =
                role === "CHECKPOINT" ||
                role === "CHECKPOINT_NODE" ||
                role === "CHECKPOINT NODE";

            const isNotDisabled = status !== "DISABLED";

            const isProvisioned =
                node.is_provisioned === true ||
                node.is_provisioned === "true" ||
                node.is_provisioned === 1 ||
                node.is_provisioned === undefined;

            return isCheckpoint && isNotDisabled && isProvisioned;
        });
    }, [nodes]);
}