/**
 * @file useCheckpointSearch.js
 * @author Farros Ramzy (you@domain.com)
 * @description Hook for searchable checkpoint destination selection.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { useMemo, useState } from "react";

import {
    filterCheckpointNodesByKeyword,
    findCheckpointNodeByInput,
    getCheckpointDisplayName,
    getCheckpointNodes,
    getCheckpointPayloadFromNode,
} from "../../utils/checkpointSearch";

export function useCheckpointSearch(nodes = []) {
    const [inputValue, setInputValue] = useState("");
    const [selectedCheckpoint, setSelectedCheckpoint] = useState(null);

    const checkpointNodes = useMemo(() => {
        return getCheckpointNodes(nodes);
    }, [nodes]);

    const filteredCheckpointNodes = useMemo(() => {
        return filterCheckpointNodesByKeyword(checkpointNodes, inputValue);
    }, [checkpointNodes, inputValue]);

    const selectedPayload = useMemo(() => {
        return getCheckpointPayloadFromNode(selectedCheckpoint);
    }, [selectedCheckpoint]);

    function handleInputChange(value) {
        setInputValue(value);

        const matchedNode = findCheckpointNodeByInput(value, checkpointNodes);

        if (matchedNode) {
            setSelectedCheckpoint(matchedNode);
            return;
        }

        setSelectedCheckpoint(null);
    }

    function selectCheckpoint(node) {
        if (!node) {
            setSelectedCheckpoint(null);
            setInputValue("");
            return;
        }

        setSelectedCheckpoint(node);
        setInputValue(getCheckpointDisplayName(node));
    }

    function clearCheckpoint() {
        setSelectedCheckpoint(null);
        setInputValue("");
    }

    return {
        inputValue,
        setInputValue: handleInputChange,

        selectedCheckpoint,
        setSelectedCheckpoint: selectCheckpoint,

        checkpointNodes,
        filteredCheckpointNodes,

        selectedPayload,

        destinationNodeId: selectedPayload.destination_node_id,
        destinationRoomName: selectedPayload.destination_room_name,

        clearCheckpoint,
        getCheckpointDisplayName,
    };
}
