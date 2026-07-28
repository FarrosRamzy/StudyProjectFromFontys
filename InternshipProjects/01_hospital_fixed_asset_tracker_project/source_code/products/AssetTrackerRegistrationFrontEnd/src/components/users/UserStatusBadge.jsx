/**
 * @file UserStatusBadge.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


export default function UserStatusBadge({ active }) {
    return (
        <span className={active ? "user-status-badge is-active" : "user-status-badge is-inactive"}>
            <span className="user-status-dot" aria-hidden="true" />
            {active ? "Active" : "Inactive"}
        </span>
    );
}
