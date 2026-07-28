/**
 * @file LoadingState.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Reusable loading state component.
 * @version 1.0.0
 * @date 2026-05-22

 * @Copyright (c) 2026
 */


export function LoadingState({
    message = "Loading...",
}) {
    return (
        <div className="loading-state" role="status" aria-live="polite">
            <span className="loading-spinner" aria-hidden="true" />

            <p>{message}</p>
        </div>
    );
}
