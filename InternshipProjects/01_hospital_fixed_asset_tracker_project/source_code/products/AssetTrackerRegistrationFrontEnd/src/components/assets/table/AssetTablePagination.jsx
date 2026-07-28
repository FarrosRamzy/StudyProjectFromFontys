/**
 * @file AssetTablePagination.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


export default function AssetTablePagination({
    currentPage,
    totalPages,
    pageInput,
    goToPreviousPage,
    goToNextPage,
    handlePageInputChange,
    handlePageInputBlur,
    handlePageInputKeyDown,
}) {
    if (totalPages <= 1) {
        return null;
    }

    return (
        <div className="simple-pagination">
            <button
                type="button"
                className="pagination-button"
                onClick={goToPreviousPage}
                disabled={currentPage <= 1}
            >
                Previous
            </button>

            <div className="pagination-page-jump">
                <span>Page</span>
                <input
                    className="pagination-page-input"
                    type="number"
                    min="1"
                    max={totalPages}
                    value={pageInput}
                    onChange={handlePageInputChange}
                    onBlur={handlePageInputBlur}
                    onKeyDown={handlePageInputKeyDown}
                />
                <span>of {totalPages}</span>
            </div>

            <button
                type="button"
                className="pagination-button"
                onClick={goToNextPage}
                disabled={currentPage >= totalPages}
            >
                Next
            </button>
        </div>
    );
}
