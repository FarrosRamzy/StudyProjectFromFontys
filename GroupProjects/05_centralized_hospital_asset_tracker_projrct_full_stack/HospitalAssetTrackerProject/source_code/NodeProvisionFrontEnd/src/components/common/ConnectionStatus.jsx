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

    return (
        <div className="connection-status">
            <button className="refresh-button" type="button" onClick={onRefresh}>
                Refresh Data
            </button>

            <p className={`connection-status-text ${tone}`}>
                Live connection:{" "}
                <strong>{formatConnectionStatus(status)}</strong>
            </p>
        </div>
    );
}