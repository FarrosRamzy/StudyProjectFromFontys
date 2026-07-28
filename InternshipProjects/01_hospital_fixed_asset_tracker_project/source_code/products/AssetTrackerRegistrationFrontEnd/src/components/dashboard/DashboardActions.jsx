/**
 * @file DashboardActions.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import DashboardActionCard from "./DashboardActionCard";

export default function DashboardActions({ canOpenNodes, canOpenAssets, canOpenUsers, navigate }) {
    return (
        <section className="panel dashboard-actions-panel">
            <div className="section-header">
                <div>
                    <h2>Quick Access</h2>
                    <p>Open the tools available for your role.</p>
                </div>
            </div>

            <div className="dashboard-actions-grid">
                {canOpenNodes && (
                    <DashboardActionCard
                        title="Node Registration"
                        message="Register, assign, identify, unassign, and edit nodes."
                        onClick={() => navigate("/nodes")}
                    />
                )}

                {canOpenAssets && (
                    <DashboardActionCard
                        title="Asset Registration"
                        message="Register, deregister, and manage movement requests."
                        onClick={() => navigate("/assets")}
                    />
                )}

                {canOpenUsers && (
                    <DashboardActionCard
                        title="User Accounts"
                        message="Create staff accounts and manage roles."
                        onClick={() => navigate("/users")}
                    />
                )}

                <DashboardActionCard
                    title="Change Password"
                    message="Update your own account password."
                    onClick={() => navigate("/account/password")}
                />
            </div>
        </section>
    );
}
