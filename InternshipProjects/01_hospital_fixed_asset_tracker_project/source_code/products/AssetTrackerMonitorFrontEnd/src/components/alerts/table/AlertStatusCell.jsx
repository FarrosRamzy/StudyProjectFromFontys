/**
 * @file AlertStatusCell.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { AssetFlowBadge } from "../../assets/AssetFlowBadge";
import { NodeStatusBadge } from "../../nodes/NodeStatusBadge";

export function AlertStatusCell({ alert }) {
    if (alert.asset) return <AssetFlowBadge flowStatus={alert.asset.flow_status} />;
    if (alert.node) return <NodeStatusBadge status={alert.node.status} />;
    return <span className="status-badge warning">Alert</span>;
}
