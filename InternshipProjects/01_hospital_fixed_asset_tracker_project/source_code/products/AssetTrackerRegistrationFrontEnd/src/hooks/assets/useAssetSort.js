/**
 * @file useAssetSort.js
 * @author Farros Ramzy (you@domain.com)
 * @description Table sorting state for registered asset data.
 * @version 1.0.0
 * @date 2026-05-12

 * @Copyright (c) 2026
 */


import { useMemo, useState } from "react";

const textSorter = new Intl.Collator(undefined, {
    numeric: true,
    sensitivity: "base",
});

function getAssetValue(asset, key) {
    switch (key) {
        case "tag_id":
            return asset.tag_id || "";

        case "item_name":
            return asset.item_name || "";

        case "status":
            return `${asset.status || ""} ${asset.flow_status || ""}`;

        case "location":
            return asset.last_location || asset.last_room_name || "";

        case "last_seen_at":
            return asset.last_seen_at || "";

        default:
            return asset[key] || "";
    }
}

function compareText(valueA, valueB, direction) {
    const result = textSorter.compare(
        String(valueA || ""),
        String(valueB || "")
    );

    return direction === "asc" ? result : -result;
}

function compareDate(valueA, valueB, direction) {
    const timeA = valueA ? new Date(valueA).getTime() : 0;
    const timeB = valueB ? new Date(valueB).getTime() : 0;

    const safeTimeA = Number.isNaN(timeA) ? 0 : timeA;
    const safeTimeB = Number.isNaN(timeB) ? 0 : timeB;

    return direction === "asc"
        ? safeTimeA - safeTimeB
        : safeTimeB - safeTimeA;
}

function compareAssets(assetA, assetB, sortKey, sortDirection) {
    const valueA = getAssetValue(assetA, sortKey);
    const valueB = getAssetValue(assetB, sortKey);

    if (sortKey === "last_seen_at") {
        return compareDate(valueA, valueB, sortDirection);
    }

    const mainResult = compareText(valueA, valueB, sortDirection);

    if (mainResult !== 0) {
        return mainResult;
    }

    return compareText(assetA.tag_id, assetB.tag_id, sortDirection);
}

export function useAssetSort(assets = []) {
    const [sortKey, setSortKey] = useState("tag_id");
    const [sortDirection, setSortDirection] = useState("asc");

    const sortedAssets = useMemo(() => {
        return [...assets].sort((assetA, assetB) => {
            return compareAssets(assetA, assetB, sortKey, sortDirection);
        });
    }, [assets, sortKey, sortDirection]);

    function handleSort(nextSortKey) {
        if (nextSortKey === sortKey) {
            setSortDirection((currentDirection) =>
                currentDirection === "asc" ? "desc" : "asc"
            );

            return;
        }

        setSortKey(nextSortKey);
        setSortDirection("asc");
    }

    function getSortLabel(label, key) {
        if (sortKey !== key) {
            return label;
        }

        return `${label} ${sortDirection === "asc" ? "▼" : "▲"}`;
    }

    return {
        sortedAssets,
        sortKey,
        sortDirection,
        handleSort,
        getSortLabel,
    };
}
