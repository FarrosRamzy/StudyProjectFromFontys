/**
 * @file useNodeSearch.js
 * @author Farros Ramzy (you@domain.com)
 * @description Search/filter logic for node table data.
 * @version 1.0.0
 * @date 2026-05-11

 * @Copyright (c) 2026
 */

import { useMemo, useState } from "react";

export function useNodeSearch(nodes = []) {
    const [searchTerm, setSearchTerm] = useState("");

    const filteredNodes = useMemo(() => {
        const query = searchTerm.trim().toLowerCase();

        if (!query) {
            return nodes;
        }

        return nodes.filter((node) => {
            const searchableText = [
                node.device_id,
                node.alias,
                node.role,
                node.status,
                node.hospital_id,
                node.hospital_name,
                node.room_name,
                node.last_ping_at,
            ]
                .filter(Boolean)
                .join(" ")
                .toLowerCase();

            return searchableText.includes(query);
        });
    }, [nodes, searchTerm]);

    return {
        searchTerm,
        setSearchTerm,
        filteredNodes,
    };
}