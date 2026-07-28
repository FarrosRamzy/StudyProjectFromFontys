/**
 * @file EmptyState.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Reusable empty-state block for tables, cards, and panels.
 * @version 1.0.0
 * @date 2026-05-22

 * @Copyright (c) 2026
 */


export function EmptyState({
    title = "No data found",
    message = "There is nothing to display yet.",
    actionLabel = "",
    onAction,
}) {
    return (
        <div className="empty-state">
            <div className="empty-state-icon" aria-hidden="true">
                —
            </div>

            <strong>{title}</strong>

            <p>{message}</p>

            {actionLabel && onAction && (
                <button
                    type="button"
                    className="secondary-button"
                    onClick={onAction}
                >
                    {actionLabel}
                </button>
            )}
        </div>
    );
}
