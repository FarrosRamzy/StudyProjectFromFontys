/**
 * @file ConnectionStatus.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Shared live connection status component.
 * @version 1.0.0
 * @date 2026-05-11

 * @Copyright (c) 2026
 */

import {
    formatConnectionStatus,
    formatConnectionTone,
} from "../../utils/nodeFormatters";

export default function ConnectionStatus({ status, onRefresh }) {
    const tone = formatConnectionTone(status);
    const statusLabel = formatConnectionStatus(status);
    const isConnected = tone === "success";

    return (
        <div className="hero-status-card">
            <button
                className="hero-refresh-button"
                type="button"
                onClick={onRefresh}
            >
                Refresh Data
            </button>

            <div className={`hero-live-status ${tone}`}>
                <span
                    className={
                        isConnected
                            ? "status-dot online"
                            : "status-dot"
                    }
                />

                <div>
                    <span>Live connection</span>
                    <strong>{statusLabel}</strong>
                </div>
            </div>
        </div>
    );
}