/**
 * @file useRegistrationNodes.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-08

 * @Copyright (c) 2026
 */

import { useMemo } from "react";

export function useRegistrationNodes(nodes) {
    return useMemo(() => {
        return nodes.filter(
            (node) => node.role === "REGISTRATION" && node.is_provisioned
        );
    }, [nodes]);
}