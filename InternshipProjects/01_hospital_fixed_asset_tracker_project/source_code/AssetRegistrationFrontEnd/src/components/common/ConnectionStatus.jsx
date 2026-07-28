/**
 * @file ConnectionStatus.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-08

 * @Copyright (c) 2026
 */

export default function ConnectionStatus({ status, onRefresh }) {
  const normalizedStatus = String(status || "").toLowerCase();

  return (
    <div className="connection-status">
      <button className="refresh-button" type="button" onClick={onRefresh}>
        Refresh Data
      </button>

      <p className={`connection-status-text ${normalizedStatus}`}>
        Live connection: <strong>{status}</strong>
      </p>
    </div>
  );
}