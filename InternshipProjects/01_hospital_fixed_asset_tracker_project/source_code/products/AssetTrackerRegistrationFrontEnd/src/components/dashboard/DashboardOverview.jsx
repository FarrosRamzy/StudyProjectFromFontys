/**
 * @file DashboardOverview.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import DashboardCard from "./DashboardCard";

export default function DashboardOverview({
    canOpenNodes,
    canOpenAssets,
    navigate,
    assets,
    nodes,
    summary,
}) {
    return (
        <section className="panel dashboard-overview-panel">
            <div className="section-header">
                <div>
                    <h2>Overview</h2>
                    <p>Quick summary of registration-side activity.</p>
                </div>
            </div>

            <div className="registration-dashboard-grid">
                {canOpenNodes && (
                    <DashboardCard
                        label="Node Registration"
                        value={nodes.length}
                        detail={
                            `${summary.onlineNodes.length} online · ` +
                            `${summary.offlineNodes.length} offline · ` +
                            `${summary.disabledNodes.length} disabled`
                        }
                        tone="info"
                        onClick={() => navigate("/nodes")}
                    />
                )}

                {canOpenAssets && (
                    <DashboardCard
                        label="Asset Registration"
                        value={assets.length}
                        detail={`${summary.activeAssets.length} active`}
                        tone="success"
                        onClick={() => navigate("/assets")}
                    />
                )}

                {canOpenAssets && (
                    <DashboardCard
                        label="Pending Placement"
                        value={summary.pendingPlacementAssets.length}
                        detail="Not placed yet"
                        tone="warning"
                        onClick={() => navigate("/assets?tab=movement")}
                    />
                )}

                {canOpenAssets && (
                    <DashboardCard
                        label="Movement Requests"
                        value={summary.pendingRequests.length}
                        detail="Waiting approval"
                        tone="warning"
                        onClick={() => navigate("/assets?tab=movement")}
                    />
                )}

                {canOpenAssets && (
                    <DashboardCard
                        label="Asset Warnings"
                        value={summary.warningAssets.length}
                        detail="Location issues"
                        tone="danger"
                        onClick={() => navigate("/assets")}
                    />
                )}
            </div>
        </section>
    );
}
