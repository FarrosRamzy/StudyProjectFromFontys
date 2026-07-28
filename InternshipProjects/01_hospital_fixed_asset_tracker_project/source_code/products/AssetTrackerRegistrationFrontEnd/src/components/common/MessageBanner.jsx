/**
 * @file MessageBanner.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Shared error/success message banner.
 * @version 1.0.0
 * @date 2026-05-11

 * @Copyright (c) 2026
 */


import { forwardRef } from "react";

function formatMessage(message) {
    return String(message || "")
        .split("\n")
        .map((line, index) => {
            if (!line) {
                return <br key={index} />;
            }

            return (
                <span key={index}>
                    {line}
                    <br />
                </span>
            );
        });
}

const MessageBanner = forwardRef(function MessageBanner(
    { error, successMessage },
    ref
) {
    if (!error && !successMessage) {
        return null;
    }

    return (
        <div ref={ref} className={error ? "message-focus-anchor" : ""}>
            {error && (
                <div className="alert alert-error">
                    {formatMessage(error)}
                </div>
            )}

            {successMessage && (
                <div className="alert alert-success">
                    {formatMessage(successMessage)}
                </div>
            )}
        </div>
    );
});

export default MessageBanner;
