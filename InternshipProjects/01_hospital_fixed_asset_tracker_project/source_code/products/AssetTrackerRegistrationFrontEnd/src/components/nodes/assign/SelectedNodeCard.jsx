/**
 * @file SelectedNodeCard.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import { formatNodeId, formatNodeStatus } from "../../../utils/nodeFormatters";

export default function SelectedNodeCard({ selectedNode }) {
    if (!selectedNode?.device_id) {
        return (
            <div className="empty-state">
                <h2>No node selected</h2>
                <p>Choose a node from the table below before assigning or editing it.</p>
            </div>
        );
    }

    return (
        <div className="tag-card">
            <span className="tag-card-label">Selected Node</span>
            <strong>{formatNodeId(selectedNode)}</strong>
            <small>Status: {formatNodeStatus(selectedNode.status)}</small>
        </div>
    );
}
