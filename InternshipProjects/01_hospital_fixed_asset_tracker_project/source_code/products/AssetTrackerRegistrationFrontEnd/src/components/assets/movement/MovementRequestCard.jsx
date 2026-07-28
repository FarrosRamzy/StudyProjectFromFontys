/**
 * @file MovementRequestCard.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import { formatDateTime } from "../../../utils/assetFormatters";

export default function MovementRequestCard({
    request,
    isActing,
    canActOnMovementRequest,
    onApprove,
    onReject,
}) {
    return (
        <article className="movement-request-card">
            <div className="movement-request-main">
                <div>
                    <h3>{request.item_name || "Unnamed Asset"}</h3>
                    <p className="movement-request-tag">{request.tag_id || "-"}</p>
                </div>

                <div className="movement-route">
                    <span>{request.from_room_name || "-"}</span>
                    <strong>→</strong>
                    <span>{request.destination_room_name || "-"}</span>
                </div>

                <div className="movement-request-meta">
                    {formatDateTime(request.requested_at)}
                </div>

                {request.note && (
                    <p className="movement-request-note">{request.note}</p>
                )}
            </div>

            <div className="movement-request-actions">
                <button
                    type="button"
                    className="small-button"
                    disabled={isActing || !canActOnMovementRequest}
                    onClick={() => onApprove(request)}
                >
                    {isActing ? "Working..." : "Approve"}
                </button>

                <button
                    type="button"
                    className="danger-small-button"
                    disabled={isActing || !canActOnMovementRequest}
                    onClick={() => onReject(request)}
                >
                    Reject
                </button>
            </div>
        </article>
    );
}
