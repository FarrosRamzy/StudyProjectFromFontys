/**
 * @file MessageBanner.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-07

 * @Copyright (c) 2026
 */

export default function MessageBanner({ error, successMessage }) {
    if (!error && !successMessage) {
        return null;
    }

    return (
        <>
            {error && <div className="alert alert-error">{error}</div>}

            {successMessage && (
                <div className="alert alert-success">{successMessage}</div>
            )}
        </>
    );
}