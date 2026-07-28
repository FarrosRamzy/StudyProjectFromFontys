/**
 * @file useNodeTable.js
 * @author Farros Ramzy (you@domain.com)
 * @description Table state for searching, sorting, and paginating node data.
 * @version 1.0.0
 * @date 2026-05-11

 * @Copyright (c) 2026
 */


import { useMemo, useState } from "react";
import { useNodeSearch } from "./useNodeSearch";
import { usePagination } from "../usePagination";

const textSorter = new Intl.Collator(undefined, {
    numeric: true,
    sensitivity: "base",
});

function getNodeValue(node, key) {
    switch (key) {
        case "device":
            return node.alias || node.device_id || "";

        case "role":
            return node.role || "";

        case "status":
            return node.status || "";

        case "hospital":
            return node.hospital_name || node.hospital_id || "";

        case "location":
            return node.room_name || "";

        case "last_ping_at":
            return node.last_ping_at || "";

        default:
            return node[key] || "";
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

function compareNodes(nodeA, nodeB, sortKey, sortDirection) {
    const valueA = getNodeValue(nodeA, sortKey);
    const valueB = getNodeValue(nodeB, sortKey);

    if (sortKey === "last_ping_at") {
        return compareDate(valueA, valueB, sortDirection);
    }

    const mainResult = compareText(valueA, valueB, sortDirection);

    if (mainResult !== 0) {
        return mainResult;
    }

    // Stable fallback: if two display values are equal, sort by full device ID.
    return compareText(nodeA.device_id, nodeB.device_id, sortDirection);
}

export function useNodeTable(nodes = [], pageSize = 5) {
    const { searchTerm, setSearchTerm, filteredNodes } = useNodeSearch(nodes);

    const [sortKey, setSortKey] = useState("device");
    const [sortDirection, setSortDirection] = useState("asc");

    const sortedNodes = useMemo(() => {
        return [...filteredNodes].sort((nodeA, nodeB) => {
            return compareNodes(nodeA, nodeB, sortKey, sortDirection);
        });
    }, [filteredNodes, sortKey, sortDirection]);

    const pagination = usePagination(sortedNodes, pageSize);

    function handleSort(nextSortKey) {
        if (nextSortKey === sortKey) {
            setSortDirection((currentDirection) =>
                currentDirection === "asc" ? "desc" : "asc"
            );
            pagination.resetPage();
            return;
        }

        setSortKey(nextSortKey);
        setSortDirection("asc");
        pagination.resetPage();
    }

    function handleSearchChange(event) {
        setSearchTerm(event.target.value);
        pagination.resetPage();
    }

    function getSortLabel(label, key) {
        if (sortKey !== key) {
            return label;
        }

        return `${label} ${sortDirection === "asc" ? "▼" : "▲"}`;
    }

    return {
        searchTerm,
        setSearchTerm,
        handleSearchChange,
        filteredNodes,
        sortedNodes,
        visibleNodes: pagination.visibleItems,
        sortKey,
        sortDirection,
        handleSort,
        getSortLabel,
        currentPage: pagination.currentPage,
        totalPages: pagination.totalPages,
        pageInput: pagination.pageInput,
        goToPreviousPage: pagination.goToPreviousPage,
        goToNextPage: pagination.goToNextPage,
        goToPage: pagination.goToPage,
        handlePageInputChange: pagination.handlePageInputChange,
        handlePageInputBlur: pagination.handlePageInputBlur,
        handlePageInputKeyDown: pagination.handlePageInputKeyDown,
    };
}