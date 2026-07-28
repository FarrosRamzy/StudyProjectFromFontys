/**
 * @file AssetMonitorToolbar.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { ASSET_FLOW_STATUS_OPTIONS, ASSET_STATUS_OPTIONS } from "../../constants/assetFlowStatus";

export function AssetMonitorToolbar({
    search,
    setSearch,
    assetStatus,
    setAssetStatus,
    flowStatus,
    setFlowStatus,
}) {
    return (
        <div className="monitor-toolbar">
            <input
                className="monitor-search"
                value={search}
                onChange={(event) => setSearch(event.target.value)}
                placeholder="Search asset, tag, room, status..."
            />
            <div className="toolbar-controls">
                <select value={assetStatus} onChange={(event) => setAssetStatus(event.target.value)}>
                    {ASSET_STATUS_OPTIONS.map((option) => (
                        <option key={option.value} value={option.value}>{option.label}</option>
                    ))}
                </select>
                <select value={flowStatus} onChange={(event) => setFlowStatus(event.target.value)}>
                    {ASSET_FLOW_STATUS_OPTIONS.map((option) => (
                        <option key={option.value} value={option.value}>{option.label}</option>
                    ))}
                </select>
            </div>
        </div>
    );
}
