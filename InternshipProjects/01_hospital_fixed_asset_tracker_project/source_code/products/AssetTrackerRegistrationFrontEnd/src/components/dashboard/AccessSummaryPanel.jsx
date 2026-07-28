/**
 * @file AccessSummaryPanel.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import AccessItem from "./AccessItem";

export default function AccessSummaryPanel({ canOpenNodes, canOpenAssets, canOpenUsers, role }) {
    return (
        <section className="panel">
            <div className="section-header">
                <div>
                    <h2>Your Access</h2>
                    <p>These are the registration tools available for your role.</p>
                </div>
            </div>

            <div className="summary-list">
                {canOpenNodes && (
                    <AccessItem title="Node Registration" message="Register, assign, identify, and manage nodes." />
                )}
                {canOpenAssets && (
                    <AccessItem title="Asset Registration" message="Register assets and handle movement requests." />
                )}
                {canOpenUsers && (
                    <AccessItem title="User Accounts" message="Create staff accounts and manage user access." />
                )}
                <AccessItem title="Change Password" message="Update your account password." />
                {role === "monitor_staff" && (
                    <AccessItem
                        title="Monitor Staff Notice"
                        message="Use the Monitor App for asset monitoring, alerts, nodes, and activity logs."
                    />
                )}
            </div>
        </section>
    );
}
