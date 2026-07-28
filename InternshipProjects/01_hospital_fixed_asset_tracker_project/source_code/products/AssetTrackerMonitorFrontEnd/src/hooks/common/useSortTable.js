/**
 * @file useSortTable.js
 * @author Farros Ramzy (you@domain.com)
 * @description Reusable table sorting hook for monitor tables.
 * @version 1.0.0
 * @date 2026-05-25

 * @Copyright (c) 2026
 */


import { useMemo, useState } from "react";

export function useSortableTable(items = [], sortConfig = {}) {
    const {
        defaultSortKey = "",
        defaultDirection = "asc",
        accessors = {},
    } = sortConfig;

    const [sortKey, setSortKey] = useState(defaultSortKey);
    const [sortDirection, setSortDirection] = useState(defaultDirection);

    const sortedItems = useMemo(() => {
        if (!sortKey) {
            return items;
        }

        const accessor = accessors[sortKey];

        if (!accessor) {
            return items;
        }

        return [...items].sort((a, b) => {
            const valueA = normalizeSortValue(accessor(a));
            const valueB = normalizeSortValue(accessor(b));

            if (valueA < valueB) {
                return sortDirection === "asc" ? -1 : 1;
            }

            if (valueA > valueB) {
                return sortDirection === "asc" ? 1 : -1;
            }

            return 0;
        });
    }, [items, sortKey, sortDirection, accessors]);

    function requestSort(nextSortKey) {
        if (!accessors[nextSortKey]) {
            return;
        }

        if (sortKey === nextSortKey) {
            setSortDirection((currentDirection) =>
                currentDirection === "asc" ? "desc" : "asc"
            );
            return;
        }

        setSortKey(nextSortKey);
        setSortDirection("asc");
    }

    function getSortButtonLabel(label, key) {
        if (sortKey !== key) {
            return label;
        }

        return `${label} ${sortDirection === "asc" ? "▼" : "▲"}`;
    }

    return {
        sortedItems,
        sortKey,
        sortDirection,
        requestSort,
        getSortButtonLabel,
    };
}

function normalizeSortValue(value) {
    if (value === null || value === undefined) {
        return "";
    }

    if (value instanceof Date) {
        return value.getTime();
    }

    if (typeof value === "number") {
        return value;
    }

    if (typeof value === "boolean") {
        return value ? 1 : 0;
    }

    const textValue = String(value).trim();

    if (!textValue) {
        return "";
    }

    const timestamp = tryGetDateTimestamp(textValue);

    if (timestamp !== null) {
        return timestamp;
    }

    return textValue.toLowerCase();
}

function tryGetDateTimestamp(value) {
    if (typeof value !== "string") {
        return null;
    }

    // Only treat clear date-like strings as dates.
    // This prevents normal labels/room names from being interpreted strangely.
    const looksLikeDate =
        /^\d{4}-\d{2}-\d{2}/.test(value) ||
        /^\d{1,2}\s+[A-Za-z]{3,}\s+\d{4}/.test(value) ||
        /^\d{1,2}\/\d{1,2}\/\d{4}/.test(value);

    if (!looksLikeDate) {
        return null;
    }

    const timestamp = new Date(value).getTime();

    if (Number.isNaN(timestamp)) {
        return null;
    }

    return timestamp;
}
