/**
 * @file NodeToolbar.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Node registration summary toolbar.
 * @version 1.0.0
 * @date 2026-05-05

 * @Copyright (c) 2026
 */

import {
    NODE_STATUSES,
    isNodeProvisioned,
} from "../../utils/nodeHelpers";

export default function NodeToolbar({ nodes = [] }) {
    const totalNodes = nodes.length;

    const onlineNodes = nodes.filter(
        (node) => node.status === NODE_STATUSES.ONLINE
    ).length;

    const offlineNodes = nodes.filter(
        (node) => node.status === NODE_STATUSES.OFFLINE
    ).length;

    const discoveredNodes = nodes.filter(
        (node) => node.status === NODE_STATUSES.DISCOVERED
    ).length;

    const provisionedNodes = nodes.filter((node) =>
        isNodeProvisioned(node)
    ).length;

    return (
        <section className="panel compact-panel">
            <div className="section-header">
                <div>
                    <h2>Node Overview</h2>
                    <p>
                        Live summary of registered and discovered nodes.
                    </p>
                </div>
            </div>

            <div className="summary-grid">
                <div className="summary-card">
                    <span>Total Nodes</span>
                    <strong>{totalNodes}</strong>
                </div>

                <div className="summary-card">
                    <span>Online</span>
                    <strong>{onlineNodes}</strong>
                </div>

                <div className="summary-card">
                    <span>Offline</span>
                    <strong>{offlineNodes}</strong>
                </div>

                <div className="summary-card">
                    <span>Discovered</span>
                    <strong>{discoveredNodes}</strong>
                </div>

                <div className="summary-card">
                    <span>Provisioned</span>
                    <strong>{provisionedNodes}</strong>
                </div>
            </div>
        </section>
    );
}