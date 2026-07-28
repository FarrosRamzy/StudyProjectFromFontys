/**
 * @file useMovementRequestModal.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { useEffect, useMemo, useState } from "react";
import { getPendingMovementRequestForAsset } from "../../utils/assets/movementRequestLookup";

export function useMovementRequestModal({ asset, movementRequests, submitting, onClose }) {
    const [destinationNodeId, setDestinationNodeId] = useState("");
    const [destinationRoomName, setDestinationRoomName] = useState("");
    const [reason, setReason] = useState("");
    const [localError, setLocalError] = useState("");

    useEffect(() => {
        function handleKeyDown(event) {
            if (event.key === "Escape" && !submitting) onClose?.();
        }
        window.addEventListener("keydown", handleKeyDown);
        return () => window.removeEventListener("keydown", handleKeyDown);
    }, [onClose, submitting]);

    useEffect(() => {
        document.body.classList.add("modal-open");
        return () => document.body.classList.remove("modal-open");
    }, []);

    const existingPendingRequest = useMemo(() => {
        const status = String(asset?.flow_status || "").toLowerCase();
        const activeId = asset?.active_movement_request_id || asset?.activeMovementRequestId;
        if (status !== "movement_requested" || !activeId) return null;
        return getPendingMovementRequestForAsset(asset, movementRequests);
    }, [asset, movementRequests]);

    function handleCheckpointChange(payload) {
        setDestinationNodeId(payload.destination_node_id || "");
        setDestinationRoomName(payload.destination_room_name || "");
        setLocalError("");
    }

    return {
        destinationNodeId, destinationRoomName, reason, setReason, localError,
        setLocalError, existingPendingRequest, handleCheckpointChange,
    };
}
