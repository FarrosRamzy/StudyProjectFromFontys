/**
 * @file MovementRequestModal.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Modal form for submitting asset movement requests.
 * @version 1.0.0
 * @date 2026-05-22

 * @Copyright (c) 2026
 */


import { DestinationCheckpointInput } from "./DestinationCheckpointInput";
import { MovementRequestReasonField } from "./MovementRequestReasonField";
import { MovementRequestSummary } from "./MovementRequestSummary";
import { useMovementRequestModal } from "../../hooks/assets/useMovementRequestModal";

export function MovementRequestModal({
    asset,
    nodes = [],
    movementRequests = [],
    submitting = false,
    onSubmit,
    onClose,
}) {
    const state = useMovementRequestModal({ asset, movementRequests, submitting, onClose });

    if (!asset) return null;

    async function handleSubmit(event) {
        event.preventDefault();
        const cleanReason = state.reason.trim();
        const error = getSubmitError(asset, state, cleanReason);
        if (error) return state.setLocalError(error);
        await onSubmit?.({
            tag_id: asset.tag_id,
            destination_node_id: state.destinationNodeId,
            destination_room_name: state.destinationRoomName,
            reason: cleanReason,
        });
    }

    const disabled = submitting || Boolean(state.existingPendingRequest);

    return (
        <div className="modal-backdrop" role="presentation" onMouseDown={() => !submitting && onClose?.()}>
            <section className="modal-card" role="dialog" aria-modal="true" aria-label="Request asset movement" onMouseDown={(event) => event.stopPropagation()}>
                <ModalHeader onClose={onClose} submitting={submitting} />
                <MovementRequestSummary asset={asset} />
                {state.existingPendingRequest && <div className="message-banner warning">This asset already has a pending movement request.</div>}
                {state.localError && <div className="message-banner error">{state.localError}</div>}
                <form className="form-stack" onSubmit={handleSubmit}>
                    <DestinationCheckpointInput nodes={nodes} disabled={disabled} onChange={state.handleCheckpointChange} />
                    <MovementRequestReasonField reason={state.reason} setReason={state.setReason} disabled={disabled} />
                    <ModalActions
                        submitting={submitting}
                        disabled={disabled || !state.destinationNodeId || !state.destinationRoomName || !state.reason.trim()}
                        onClose={onClose}
                    />
                </form>
            </section>
        </div>
    );
}

function ModalHeader({ onClose, submitting }) {
    return (
        <div className="modal-header">
            <div><h2>Request Asset Movement</h2><p>Submit a movement request for registration desk approval.</p></div>
            <button type="button" className="ghost-button small" onClick={onClose} disabled={submitting}>Close</button>
        </div>
    );
}

function ModalActions({ submitting, disabled, onClose }) {
    return (
        <div className="modal-actions">
            <button type="button" className="secondary-button" onClick={onClose} disabled={submitting}>Cancel</button>
            <button type="submit" className="primary-button" disabled={disabled}>{submitting ? "Submitting..." : "Submit Request"}</button>
        </div>
    );
}

function getSubmitError(asset, state, cleanReason) {
    if (!asset?.tag_id) return "Asset tag ID is missing.";
    if (!state.destinationNodeId || !state.destinationRoomName) return "Please select a valid destination checkpoint.";
    if (!cleanReason) return "Please enter the movement reason.";
    if (state.destinationRoomName === asset.assigned_room_name) return "Destination room is the same as the assigned room.";
    return "";
}
