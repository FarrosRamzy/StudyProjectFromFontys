/**
 * @file StatusBadge.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-07

 * @Copyright (c) 2026
 */

export default function StatusBadge({ status }) {
    const cleanStatus = String(status || "unknown").trim();
    const normalizedStatus = cleanStatus.toLowerCase();

    return (
        <span className={`asset-status ${normalizedStatus}`}>
            {cleanStatus}
        </span>
    );
}