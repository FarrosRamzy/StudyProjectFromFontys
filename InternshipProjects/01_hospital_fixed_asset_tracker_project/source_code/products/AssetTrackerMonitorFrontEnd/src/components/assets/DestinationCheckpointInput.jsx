/**
 * @file DestinationCheckpointInput.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Searchable destination checkpoint input for movement requests.
 * @version 1.0.0
 * @date 2026-05-22

 * @Copyright (c) 2026
 */


import { useCheckpointSearch } from "../../hooks/movement/useCheckpointSearch";

export function DestinationCheckpointInput({
    nodes = [],
    label = "Destination checkpoint",
    disabled = false,
    required = true,
    onChange,
}) {
    const {
        inputValue,
        setInputValue,
        selectedCheckpoint,
        filteredCheckpointNodes,
        destinationNodeId,
        destinationRoomName,
        setSelectedCheckpoint,
        clearCheckpoint,
        getCheckpointDisplayName,
    } = useCheckpointSearch(nodes);

    function handleInputChange(value) {
        setInputValue(value);

        const matchedNode = filteredCheckpointNodes.find((node) => {
            return getCheckpointDisplayName(node) === value;
        });

        const payload = matchedNode
            ? {
                destination_node_id: matchedNode.device_id || matchedNode.node_id || "",
                destination_room_name: matchedNode.room_name || "",
                checkpoint: matchedNode,
            }
            : {
                destination_node_id: "",
                destination_room_name: "",
                checkpoint: null,
            };

        onChange?.(payload);
    }

    function handleSelectNode(node) {
        setSelectedCheckpoint(node);

        onChange?.({
            destination_node_id: node.device_id || node.node_id || "",
            destination_room_name: node.room_name || "",
            checkpoint: node,
        });
    }

    function handleClear() {
        clearCheckpoint();

        onChange?.({
            destination_node_id: "",
            destination_room_name: "",
            checkpoint: null,
        });
    }

    return (
        <div className="field">
            <span>
                {label}
                {required && <strong className="required-marker"> *</strong>}
            </span>

            <div className="checkpoint-search">
                <input
                    type="text"
                    value={inputValue}
                    disabled={disabled}
                    list="destination-checkpoint-options"
                    onChange={(event) => handleInputChange(event.target.value)}
                    placeholder="Type room name, alias, or checkpoint node ID"
                />

                {inputValue && !disabled && (
                    <button
                        type="button"
                        className="ghost-button small"
                        onClick={handleClear}
                    >
                        Clear
                    </button>
                )}
            </div>

            <datalist id="destination-checkpoint-options">
                {filteredCheckpointNodes.map((node) => (
                    <option
                        key={node.device_id || node.node_id}
                        value={getCheckpointDisplayName(node)}
                    />
                ))}
            </datalist>

            {selectedCheckpoint ? (
                <div className="field-help success">
                    Selected:{" "}
                    <strong>{destinationRoomName || "Unnamed room"}</strong>
                    {" · "}
                    <span className="monitor-mono">
                        {destinationNodeId || "-"}
                    </span>
                </div>
            ) : inputValue ? (
                <div className="field-help warning">
                    Please select a valid checkpoint from the suggestions.
                </div>
            ) : (
                <div className="field-help">
                    The backend will receive the selected checkpoint node ID and room name.
                </div>
            )}
        </div>
    );
}
