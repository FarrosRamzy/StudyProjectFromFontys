/**
 * @file MovementRequestsTable.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Movement request approval/rejection panel.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import MovementRequestCard from "./movement/MovementRequestCard";
import MovementRequestToolbar from "./movement/MovementRequestToolbar";
import { isOnlineRegistrationNode } from "../../hooks/assets/movement/movementRequestHelpers";

export default function MovementRequestsTable({
    movementRequests = [],
    loading,
    actingMovementRequestId,
    registrationNodes = [],
    registrationNodeId,
    setRegistrationNodeId,
    onRefresh,
    onApprove,
    onReject,
}) {
    const selectedRegistrationNode = registrationNodes.find(
        (node) => node.device_id === registrationNodeId
    );
    const selectedRegistrationNodeIsOnline = selectedRegistrationNode
        ? isOnlineRegistrationNode(selectedRegistrationNode)
        : false;
    const canActOnMovementRequest = Boolean(registrationNodeId) && selectedRegistrationNodeIsOnline;

    return (
        <section className="movement-requests-panel">
            <div className="movement-requests-header">
                <div>
                    <h2>Movement Requests</h2>
                    <p>Select the registration desk node, then approve or reject pending asset movement requests.</p>
                </div>
                <button type="button" className="compact-secondary-button" onClick={onRefresh} disabled={loading}>
                    {loading ? "Refreshing..." : "Refresh"}
                </button>
            </div>

            <MovementRequestToolbar
                loading={loading}
                registrationNodes={registrationNodes}
                registrationNodeId={registrationNodeId}
                setRegistrationNodeId={setRegistrationNodeId}
                selectedRegistrationNodeIsOnline={selectedRegistrationNodeIsOnline}
            />
            <MovementWarnings
                registrationNodeId={registrationNodeId}
                selectedRegistrationNodeIsOnline={selectedRegistrationNodeIsOnline}
            />
            <MovementRequestList
                loading={loading}
                movementRequests={movementRequests}
                actingMovementRequestId={actingMovementRequestId}
                canActOnMovementRequest={canActOnMovementRequest}
                onApprove={onApprove}
                onReject={onReject}
            />
        </section>
    );
}

function MovementWarnings({ registrationNodeId, selectedRegistrationNodeIsOnline }) {
    if (!registrationNodeId) {
        return <div className="compact-warning">Select an online registration node first to approve or reject requests.</div>;
    }

    if (!selectedRegistrationNodeIsOnline) {
        return <div className="compact-warning">The selected registration node is offline and cannot approve or reject movement requests.</div>;
    }

    return null;
}

function MovementRequestList(props) {
    if (props.loading) {
        return <div className="compact-empty-state">Loading pending requests...</div>;
    }

    if (!props.movementRequests.length) {
        return <div className="compact-empty-state">No pending movement requests.</div>;
    }

    return (
        <div className="movement-request-list">
            {props.movementRequests.map((request) => (
                <MovementRequestCard
                    key={request.id}
                    request={request}
                    isActing={props.actingMovementRequestId === request.id}
                    canActOnMovementRequest={props.canActOnMovementRequest}
                    onApprove={props.onApprove}
                    onReject={props.onReject}
                />
            ))}
        </div>
    );
}
