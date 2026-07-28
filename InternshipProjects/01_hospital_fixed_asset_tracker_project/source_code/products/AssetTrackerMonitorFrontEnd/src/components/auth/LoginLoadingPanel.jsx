/**
 * @file LoginLoadingPanel.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


export function LoginLoadingPanel({ slowLoading }) {
    return (
        <div className="auth-loading-panel" role="status" aria-live="polite">
            <div className="auth-loading-spinner" aria-hidden="true" />
            <div>
                <strong>Connecting to the monitor system...</strong>
                <p>
                    {slowLoading
                        ? "The backend may be waking up. This can take a few seconds on Render."
                        : "Checking your account and preparing the monitor dashboard."}
                </p>
            </div>
        </div>
    );
}
