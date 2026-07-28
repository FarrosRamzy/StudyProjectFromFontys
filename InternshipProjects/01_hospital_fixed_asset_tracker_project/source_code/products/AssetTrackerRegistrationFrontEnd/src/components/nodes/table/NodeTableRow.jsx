/**
 * @file NodeTableRow.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import NodeRoleBadge from "../NodeRoleBadge";
import NodeStatusBadge from "../NodeStatusBadge";
import {
    canEditNode,
    getNodeIdentity,
} from "../../../utils/nodeHelpers";
import {
    formatLastPing,
    formatNodeHospital,
    formatNodeLocation,
    formatNodeName,
    formatShortNodeId,
} from "../../../utils/nodeFormatters";
import NodeActionButtons from "./NodeActionButtons";

export default function NodeTableRow({
    node,
    selectedNode,
    identifyingNodeId,
    onIdentifyNode,
    onSelectNode,
}) {
    const deviceId = getNodeIdentity(node);
    const actionLabel = canEditNode(node) ? "Edit" : "Assign";
    const isSelected = selectedNode?.device_id === deviceId;
    const isAssigned = Boolean(node.is_provisioned);
    const nodeStatus = String(node.status || "").toUpperCase();
    const isOffline = nodeStatus === "OFFLINE";
    const isDisabled = nodeStatus === "DISABLED";
    const showBlinkButton = isAssigned;
    const canIdentify = showBlinkButton && !isOffline && !isDisabled;
    const isIdentifying = identifyingNodeId === deviceId;

    return (
        <tr key={deviceId} className={isSelected ? "selected-row" : ""}>
            <td className="device-cell" data-label="Device">
                <strong className="device-alias">{formatNodeName(node)}</strong>
                <span className="device-id-small" title={deviceId}>
                    {formatShortNodeId(node)}
                </span>
            </td>
            <td data-label="Role"><NodeRoleBadge role={node.role} /></td>
            <td data-label="Status"><NodeStatusBadge status={node.status} /></td>
            <td data-label="Hospital">{formatNodeHospital(node)}</td>
            <td data-label="Location">{formatNodeLocation(node)}</td>
            <td data-label="Last Ping">{formatLastPing(node)}</td>
            <td className="action-col" data-label="Actions">
                <NodeActionButtons
                    node={node}
                    deviceId={deviceId}
                    actionLabel={actionLabel}
                    isSelected={isSelected}
                    showBlinkButton={showBlinkButton}
                    canIdentify={canIdentify}
                    isIdentifying={isIdentifying}
                    isOffline={isOffline}
                    isDisabled={isDisabled}
                    onIdentifyNode={onIdentifyNode}
                    onSelectNode={onSelectNode}
                />
            </td>
        </tr>
    );
}
