/**
 * @file Topbar.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Top navigation bar for the Hospital Asset Monitor app.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { WS_STATUS_META } from "../../constants/webSocketEvents";

export function Topbar({
    user,
    wsStatus = "idle",
    onRefresh,
    onLogout,
}) {
    const wsMeta = WS_STATUS_META[wsStatus] || {
        label: wsStatus || "Unknown",
        tone: "neutral",
    };

    return (
        <header className="app-topbar">
            <div className="app-brand-lockup">
                <span className="app-brand-mark">
                    <img
                        src="/stethoscope.png"
                        alt=""
                        aria-hidden="true"
                    />
                </span>

                <div>
                    <strong>Hospital Asset Tracker</strong>
                    <span>Asset Monitor Console</span>
                </div>
            </div>

            <div className="topbar-actions">
                <div
                    className="connection-pill"
                    title={`WebSocket ${wsMeta.label}`}
                    aria-label={`WebSocket ${wsMeta.label}`}
                >
                    <span
                        className={`connection-dot ${getConnectionDotClass(wsStatus)}`}
                        aria-hidden="true"
                    />

                    <strong className="connection-label-full">
                        WebSocket {wsMeta.label}
                    </strong>

                    <strong className="connection-label-short">
                        {wsMeta.label}
                    </strong>
                </div>

                <button
                    type="button"
                    className="secondary-button small"
                    onClick={onRefresh}
                >
                    Refresh
                </button>

                <div className="topbar-user">
                    <div className="topbar-user-text">
                        <span>{user?.role || "User"}</span>
                        <strong>{user?.full_name || user?.email || "Monitor User"}</strong>
                    </div>
                </div>

                <button
                    type="button"
                    className="ghost-button small"
                    onClick={onLogout}
                >
                    Sign out
                </button>
            </div>
        </header>
    );
}

function getConnectionDotClass(wsStatus) {
    if (wsStatus === "connected") {
        return "online";
    }

    if (wsStatus === "error" || wsStatus === "disconnected") {
        return "offline";
    }

    return "warning";
}
