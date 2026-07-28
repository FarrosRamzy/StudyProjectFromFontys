/**
 * @file useAssetSort.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-12

 * @Copyright (c) 2026
 */

import { useMemo, useState } from "react";

const SORT_ACCESSORS = {
    tag_id: (asset) => asset.tag_id || "",
    item_name: (asset) => asset.item_name || "",
    status: (asset) => asset.status || "",
    location: (asset) => asset.last_location || asset.last_room_name || "",
    last_seen_at: (asset) => asset.last_seen_at || "",
};

export function useAssetSort(assets = []) {
    const [sortConfig, setSortConfig] = useState({
        key: "tag_id",
        direction: "asc",
    });

    const sortedAssets = useMemo(() => {
        const accessor = SORT_ACCESSORS[sortConfig.key];

        if (!accessor) {
            return assets;
        }

        return [...assets].sort((a, b) => {
            const valueA = accessor(a);
            const valueB = accessor(b);

            if (sortConfig.key === "last_seen_at") {
                const timeA = valueA ? new Date(valueA).getTime() : 0;
                const timeB = valueB ? new Date(valueB).getTime() : 0;

                return sortConfig.direction === "asc"
                    ? timeA - timeB
                    : timeB - timeA;
            }

            const comparison = String(valueA).localeCompare(String(valueB), undefined, {
                numeric: true,
                sensitivity: "base",
            });

            return sortConfig.direction === "asc" ? comparison : -comparison;
        });
    }, [assets, sortConfig]);

    function handleSort(key) {
        setSortConfig((current) => {
            if (current.key === key) {
                return {
                    key,
                    direction: current.direction === "asc" ? "desc" : "asc",
                };
            }

            return {
                key,
                direction: "asc",
            };
        });
    }

    function getSortIndicator(key) {
        if (sortConfig.key !== key) {
            return "";
        }

        return sortConfig.direction === "asc" ? " ↓" : " ↑";
    }

    return {
        sortedAssets,
        sortConfig,
        handleSort,
        getSortIndicator,
    };
}