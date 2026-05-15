/**
 * @file usePagination.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-08

 * @Copyright (c) 2026
 */

import { useEffect, useMemo, useState } from "react";

export function usePagination(items = [], pageSize = 5) {
    const [currentPage, setCurrentPage] = useState(1);
    const [pageInput, setPageInput] = useState("1");

    const totalItems = items.length;
    const totalPages = Math.max(1, Math.ceil(totalItems / pageSize));
    const safeCurrentPage = Math.min(currentPage, totalPages);

    const visibleItems = useMemo(() => {
        const startIndex = (safeCurrentPage - 1) * pageSize;
        const endIndex = startIndex + pageSize;

        return items.slice(startIndex, endIndex);
    }, [items, safeCurrentPage, pageSize]);

    useEffect(() => {
        if (currentPage > totalPages) {
            setCurrentPage(totalPages);
        }
    }, [currentPage, totalPages]);

    useEffect(() => {
        setPageInput(String(safeCurrentPage));
    }, [safeCurrentPage]);

    function goToPreviousPage() {
        setCurrentPage((page) => Math.max(1, page - 1));
    }

    function goToNextPage() {
        setCurrentPage((page) => Math.min(totalPages, page + 1));
    }

    function goToPage(pageNumber) {
        const numericPage = Number(pageNumber);

        if (!Number.isFinite(numericPage)) {
            setPageInput(String(safeCurrentPage));
            return;
        }

        const clampedPage = Math.min(
            Math.max(1, Math.trunc(numericPage)),
            totalPages
        );

        setCurrentPage(clampedPage);
        setPageInput(String(clampedPage));
    }

    function handlePageInputChange(event) {
        setPageInput(event.target.value);
    }

    function handlePageInputBlur() {
        goToPage(pageInput);
    }

    function handlePageInputKeyDown(event) {
        if (event.key === "Enter") {
            goToPage(pageInput);
            event.currentTarget.blur();
        }
    }

    function resetPage() {
        setCurrentPage(1);
    }

    return {
        currentPage: safeCurrentPage,
        totalPages,
        visibleItems,

        pageInput,
        resetPage,
        handlePageInputChange,
        handlePageInputBlur,
        handlePageInputKeyDown,

        goToPreviousPage,
        goToNextPage,
    };
}