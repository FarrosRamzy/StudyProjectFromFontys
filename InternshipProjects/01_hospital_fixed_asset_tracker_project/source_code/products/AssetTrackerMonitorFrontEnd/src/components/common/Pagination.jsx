/**
 * @file Pagination.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Reusable pagination control for monitor tables.
 * @version 1.0.0
 * @date 2026-05-25

 * @Copyright (c) 2026
 */


import { useEffect, useState } from "react";

export function Pagination({
    page,
    totalPages,
    totalItems,
    pageSize,
    onPageChange,
}) {
    const [pageInput, setPageInput] = useState(String(page));

    useEffect(() => {
        setPageInput(String(page));
    }, [page]);

    if (totalItems <= pageSize) {
        return null;
    }

    function goPrevious() {
        onPageChange(Math.max(page - 1, 1));
    }

    function goNext() {
        onPageChange(Math.min(page + 1, totalPages));
    }

    function commitPageInput() {
        const trimmedValue = String(pageInput).trim();

        if (!trimmedValue) {
            setPageInput(String(page));
            return;
        }

        const requestedPage = Number(trimmedValue);

        if (!Number.isInteger(requestedPage)) {
            setPageInput(String(page));
            return;
        }

        const safePage = Math.min(
            Math.max(requestedPage, 1),
            totalPages
        );

        onPageChange(safePage);
        setPageInput(String(safePage));
    }

    function handlePageInputKeyDown(event) {
        if (event.key === "Enter") {
            commitPageInput();
            event.currentTarget.blur();
        }

        if (event.key === "Escape") {
            setPageInput(String(page));
            event.currentTarget.blur();
        }
    }

    return (
        <div className="pagination-bar">
            <button
                type="button"
                className="secondary-button small"
                disabled={page <= 1}
                onClick={goPrevious}
            >
                Previous
            </button>

            <div className="pagination-page-control">
                <span>Page</span>

                <input
                    type="text"
                    inputMode="numeric"
                    pattern="[0-9]*"
                    value={pageInput}
                    onChange={(event) => {
                        const value = event.target.value;

                        if (/^\d*$/.test(value)) {
                            setPageInput(value);
                        }
                    }}
                    onBlur={commitPageInput}
                    onKeyDown={handlePageInputKeyDown}
                    aria-label="Current page"
                />

                <span>of {totalPages}</span>
            </div>

            <button
                type="button"
                className="secondary-button small"
                disabled={page >= totalPages}
                onClick={goNext}
            >
                Next
            </button>
        </div>
    );
}
