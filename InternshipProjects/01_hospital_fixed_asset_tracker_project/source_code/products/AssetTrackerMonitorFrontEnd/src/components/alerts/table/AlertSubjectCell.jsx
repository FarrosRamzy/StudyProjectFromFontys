/**
 * @file AlertSubjectCell.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { formatTagId } from "../../../utils/textFormat";

export function AlertSubjectCell({ alert }) {
    if (alert.asset) {
        return (
            <><strong>{alert.asset.item_name || "Unnamed asset"}</strong><div className="monitor-muted monitor-mono" title={alert.asset.tag_id}>{formatTagId(alert.asset.tag_id)}</div></>
        );
    }
    if (alert.node) {
        return (
            <><strong>{alert.node.alias || alert.node.device_id || "Node"}</strong><div className="monitor-muted monitor-mono">{alert.node.device_id}</div></>
        );
    }
    return <strong>{alert.title || "Alert"}</strong>;
}
