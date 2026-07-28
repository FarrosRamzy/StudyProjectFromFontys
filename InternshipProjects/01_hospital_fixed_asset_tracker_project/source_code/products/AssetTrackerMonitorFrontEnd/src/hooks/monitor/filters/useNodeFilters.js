/**
 * @file useNodeFilters.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { useMemo, useState } from "react";
import { includesSearchKeyword } from "../../../utils/textFormat";
import { getNormalizedNodeRoleGroup, getNormalizedNodeStatusGroup } from "./nodeFilterHelpers";

export function useNodeFilters(nodes = []) {
    const [search, setSearch] = useState("");
    const [nodeStatus, setNodeStatus] = useState("all");
    const [nodeRole, setNodeRole] = useState("all");

    const filteredNodes = useMemo(() => nodes.filter((node) => {
        const matchesSearch = includesSearchKeyword([
            node.device_id, node.node_id, node.alias, node.role, node.status,
            node.room_name, node.hospital_name,
            node.is_provisioned ? "provisioned" : "unknown discovered unprovisioned",
        ], search);
        const matchesStatus = nodeStatus === "all" ||
            getNormalizedNodeStatusGroup(node) === nodeStatus;
        const matchesRole = nodeRole === "all" ||
            getNormalizedNodeRoleGroup(node.role) === nodeRole;
        return matchesSearch && matchesStatus && matchesRole;
    }), [nodes, search, nodeStatus, nodeRole]);

    return { search, setSearch, nodeStatus, setNodeStatus, nodeRole, setNodeRole, filteredNodes };
}
