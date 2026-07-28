/**
 * @file ErrorBanner.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Reusable error message banner.
 * @version 1.0.0
 * @date 2026-05-22

 * @Copyright (c) 2026
 */


export function ErrorBanner({
    title = "Something went wrong",
    message = "",
    actionLabel = "",
    onAction,
}) {
    return (
        <div className="message-banner error">
            <div>
                <strong>{title}</strong>

                {message && <p>{message}</p>}
            </div>

            {actionLabel && onAction && (
                <button
                    type="button"
                    className="secondary-button small"
                    onClick={onAction}
                >
                    {actionLabel}
                </button>
            )}
        </div>
    );
}
