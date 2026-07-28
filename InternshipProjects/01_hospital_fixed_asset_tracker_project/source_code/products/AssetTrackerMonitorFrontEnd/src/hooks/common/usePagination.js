/**
 * @file usePagination.js
 * @author Farros Ramzy (you@domain.com)
 * @description Reusable client-side pagination hook.
 * @version 1.0.0
 * @date 2026-05-25

 * @Copyright (c) 2026
 */


import { useEffect, useMemo, useState } from "react";

export function usePagination(items = [], pageSize = 10, resetKeys = []) {
    const [currentPage, setCurrentPage] = useState(1);

    const totalItems = items.length;
    const totalPages = Math.max(1, Math.ceil(totalItems / pageSize));
    const safeCurrentPage = Math.min(currentPage, totalPages);

    const paginatedItems = useMemo(() => {
        const startIndex = (safeCurrentPage - 1) * pageSize;
        const endIndex = startIndex + pageSize;

        return items.slice(startIndex, endIndex);
    }, [items, safeCurrentPage, pageSize]);

    useEffect(() => {
        setCurrentPage(1);
        // eslint-disable-next-line react-hooks/exhaustive-deps
    }, resetKeys);

    useEffect(() => {
        if (currentPage > totalPages) {
            setCurrentPage(totalPages);
        }
    }, [currentPage, totalPages]);

    return {
        currentPage: safeCurrentPage,
        setCurrentPage,
        totalItems,
        totalPages,
        pageSize,
        paginatedItems,
    };
}
