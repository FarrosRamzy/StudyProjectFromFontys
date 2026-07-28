/**
 * @file SortHeader.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


export function SortHeader({
    label,
    sortKey,
    activeSortKey,
    getSortButtonLabel,
    onSort,
}) {
    return (
        <button
            type="button"
            className={`sort-button ${activeSortKey === sortKey ? "active" : ""}`}
            onClick={() => onSort(sortKey)}
        >
            {getSortButtonLabel(label, sortKey)}
        </button>
    );
}
