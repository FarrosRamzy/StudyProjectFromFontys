/**
 * @file AttentionSummaryPanel.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import AccessItem from "./AccessItem";

export default function AttentionSummaryPanel({ canOpenNodes, canOpenAssets, summary }) {
    const hasPending = canOpenAssets && summary.pendingRequests.length > 0;
    const hasWarnings = canOpenAssets && summary.warningAssets.length > 0;
    const hasOffline = canOpenNodes && summary.offlineNodes.length > 0;

    return (
        <section className="panel">
            <div className="section-header">
                <div>
                    <h2>Attention Summary</h2>
                    <p>Important registration-side items.</p>
                </div>
            </div>

            <div className="summary-list">
                {hasPending && (
                    <AccessItem
                        title={`${summary.pendingRequests.length} pending movement request${summary.pendingRequests.length === 1 ? "" : "s"}`}
                        message="Open Asset Registration to approve or reject movement requests."
                        tone="warning"
                    />
                )}

                {hasWarnings && (
                    <AccessItem
                        title={`${summary.warningAssets.length} asset warning${summary.warningAssets.length === 1 ? "" : "s"}`}
                        message="Some assets are in the wrong location or moved without approval."
                        tone="danger"
                    />
                )}

                {hasOffline && (
                    <AccessItem
                        title={`${summary.offlineNodes.length} node issue${summary.offlineNodes.length === 1 ? "" : "s"}`}
                        message="Some nodes are offline or disabled."
                        tone="warning"
                    />
                )}

                {!hasPending && !hasWarnings && !hasOffline && (
                    <div className="empty-state">
                        <p>No urgent registration-side action.</p>
                    </div>
                )}
            </div>
        </section>
    );
}
