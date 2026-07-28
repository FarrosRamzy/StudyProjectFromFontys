/**
 * @file StatusBadge.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Generic reusable status badge component.
 * @version 1.0.0
 * @date 2026-05-22

 * @Copyright (c) 2026
 */


export function StatusBadge({
    children,
    tone = "neutral",
    title = "",
    className = "",
}) {
    return (
        <span
            className={`status-badge ${tone} ${className}`.trim()}
            title={title}
        >
            {children}
        </span>
    );
}
