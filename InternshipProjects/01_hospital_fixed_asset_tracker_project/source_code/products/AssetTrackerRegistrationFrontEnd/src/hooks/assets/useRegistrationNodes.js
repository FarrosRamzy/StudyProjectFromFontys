/**
 * @file useRegistrationNodes.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-08

 * @Copyright (c) 2026
 */


import { useMemo } from "react";

function normalizeText(value) {
    return String(value || "").trim().toUpperCase();
}

export function useRegistrationNodes(nodes) {
    return useMemo(() => {
        return nodes.filter((node) => {
            const role = normalizeText(node.role);
            const status = normalizeText(node.status);

            const isRegistration =
                role === "REGISTRATION" ||
                role === "REGISTRATION_DESK" ||
                role === "REGISTRATION DESK";

            const isNotDisabled = status !== "DISABLED";

            const isProvisioned =
                node.is_provisioned === true ||
                node.is_provisioned === "true" ||
                node.is_provisioned === 1;

            return isRegistration && isNotDisabled && isProvisioned;
        });
    }, [nodes]);
}