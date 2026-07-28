/**
 * @file MonitorSummaryCards.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Summary cards for the monitor dashboard.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { APP_ROUTES } from "../../constants/appRoutes";
import { ASSET_FLOW_STATUS } from "../../constants/assetFlowStatus";
import { NODE_STATUS } from "../../constants/nodeStatus";

export function MonitorSummaryCards({
    assets = [],
    nodes = [],
    movementRequests = [],
    alerts = [],
    onNavigate,
}) {
    const activeAssets = assets.filter((asset) => asset.status === "active");

    const availableAssets = assets.filter(
        (asset) => asset.flow_status === ASSET_FLOW_STATUS.AVAILABLE
    );

    const pendingPlacementAssets = assets.filter(
        (asset) => asset.flow_status === ASSET_FLOW_STATUS.PENDING_PLACEMENT
    );

    const waitingApprovalAssets = assets.filter(
        (asset) => asset.flow_status === ASSET_FLOW_STATUS.MOVEMENT_REQUESTED
    );

    const inTransitAssets = assets.filter(
        (asset) => asset.flow_status === ASSET_FLOW_STATUS.IN_TRANSIT
    );

    const wrongLocationAssets = assets.filter(
        (asset) => asset.flow_status === ASSET_FLOW_STATUS.WRONG_LOCATION
    );

    const unauthorizedMovementAssets = assets.filter(
        (asset) => asset.flow_status === ASSET_FLOW_STATUS.UNAUTHORIZED_MOVEMENT
    );

    const onlineNodes = nodes.filter((node) => {
        const status = String(node.status || "").toUpperCase();

        return (
            status === NODE_STATUS.ONLINE ||
            status === NODE_STATUS.ACTIVE ||
            status === NODE_STATUS.CONNECTED
        );
    });

    const offlineNodes = nodes.filter((node) => {
        const status = String(node.status || "").toUpperCase();

        return status === NODE_STATUS.OFFLINE || status === NODE_STATUS.DISABLED;
    });

    const pendingMovementRequests = movementRequests.filter((request) => {
        return String(request.status || "").toLowerCase() === "pending";
    });

    const warningCount =
        wrongLocationAssets.length +
        unauthorizedMovementAssets.length +
        alerts.length;

    return (
        <div className="monitor-summary-grid">
            <SummaryCard
                label="Registered Assets"
                value={assets.length}
                detail={`${activeAssets.length} active assets`}
                tone="success"
                onClick={() => onNavigate?.(APP_ROUTES.ASSETS)}
            />

            <SummaryCard
                label="In Place"
                value={availableAssets.length}
                detail="Assets in assigned location"
                tone="success"
                onClick={() => onNavigate?.(APP_ROUTES.ASSETS)}
            />

            <SummaryCard
                label="Pending Placement"
                value={pendingPlacementAssets.length}
                detail="Registered but not yet placed"
                tone="danger"
                onClick={() => onNavigate?.(APP_ROUTES.ASSETS)}
            />

            <SummaryCard
                label="Movement"
                value={waitingApprovalAssets.length + inTransitAssets.length}
                detail={`${waitingApprovalAssets.length} waiting, ${inTransitAssets.length} moving`}
                tone="warning"
                onClick={() => onNavigate?.(APP_ROUTES.ASSETS)}
            />

            <SummaryCard
                label="Pending Requests"
                value={pendingMovementRequests.length}
                detail="Waiting for registration desk approval"
                tone="warning"
                onClick={() => onNavigate?.(APP_ROUTES.ASSETS)}
            />

            <SummaryCard
                label="Warnings"
                value={warningCount}
                detail={`${wrongLocationAssets.length} wrong, ${unauthorizedMovementAssets.length} unauthorized`}
                tone="danger"
                onClick={() => onNavigate?.(APP_ROUTES.ALERTS)}
            />

            <SummaryCard
                label="Online Nodes"
                value={onlineNodes.length}
                detail={`${offlineNodes.length} offline or disabled`}
                tone="success"
                onClick={() => onNavigate?.(APP_ROUTES.NODES)}
            />

            <SummaryCard
                label="Total Nodes"
                value={nodes.length}
                detail="Registration and checkpoint nodes"
                tone="info"
                onClick={() => onNavigate?.(APP_ROUTES.NODES)}
            />
        </div>
    );
}

function SummaryCard({ label, value, detail, tone = "neutral", onClick }) {
    return (
        <button
            type="button"
            className={`monitor-stat-card ${tone}`}
            onClick={onClick}
        >
            <span>{label}</span>
            <strong>{value}</strong>
            <p>{detail}</p>
        </button>
    );
}
