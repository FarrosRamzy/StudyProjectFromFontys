/**
 * @file RegistrationDashboard.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-15

 * @Copyright (c) 2026
 */


import { useNavigate } from "react-router-dom";
import DashboardActions from "../components/dashboard/DashboardActions";
import DashboardOverview from "../components/dashboard/DashboardOverview";
import AccessSummaryPanel from "../components/dashboard/AccessSummaryPanel";
import AttentionSummaryPanel from "../components/dashboard/AttentionSummaryPanel";
import MessageBanner from "../components/common/MessageBanner";
import RegistrationModuleNav from "../components/common/RegistrationModuleNav";
import RegistrationTopbar from "../components/common/RegistrationTopbar";
import { useAuth } from "../context/AuthContext";
import { useAuthActions } from "../hooks/useAuthAction";
import { useRegistrationDashboardData } from "../hooks/dashboard/useRegistrationDashboardData";
import { useRegistrationDashboardSummary } from "../hooks/dashboard/useRegistrationDashboardSummary";
import { normalizeRole } from "../utils/userAdminPolicy";
import {
    canAccessAssetRegistration,
    canAccessNodeRegistration,
    canAccessUserManagement,
} from "../utils/userFormatters";

export default function RegistrationDashboard() {
    const navigate = useNavigate();
    const { user } = useAuth();
    const { handleLogout } = useAuthActions();
    const role = normalizeRole(user?.role);

    const canOpenNodes = canAccessNodeRegistration(role);
    const canOpenAssets = canAccessAssetRegistration(role);
    const canOpenUsers = canAccessUserManagement(role);
    const shouldShowOverview = canOpenNodes || canOpenAssets;

    const { assets, nodes, movementRequests, loading, error, refreshData } =
        useRegistrationDashboardData({
            loadAssets: canOpenAssets,
            loadNodes: canOpenNodes || canOpenAssets,
            loadMovementRequests: canOpenAssets,
        });

    const summary = useRegistrationDashboardSummary({
        assets,
        nodes,
        movementRequests,
    });

    return (
        <main className="app-shell registration-dashboard-page">
            <div className="sticky-page-header">
                <RegistrationTopbar
                    user={user}
                    subtitle="Registration Dashboard"
                    onRefresh={refreshData}
                    onLogout={handleLogout}
                />
                <RegistrationModuleNav role={role} />
            </div>

            <section className="page-hero">
                <div className="hero-main">
                    <p className="eyebrow">Hospital Asset Tracker</p>
                    <h1>Dashboard</h1>
                    <p className="hero-copy">Quick access to the tools available for your account role.</p>
                </div>
            </section>

            <MessageBanner error={error} successMessage="" />

            {loading ? (
                <section className="panel"><p>Loading dashboard data...</p></section>
            ) : (
                <>
                    {shouldShowOverview && (
                        <DashboardOverview
                            canOpenNodes={canOpenNodes}
                            canOpenAssets={canOpenAssets}
                            navigate={navigate}
                            assets={assets}
                            nodes={nodes}
                            summary={summary}
                        />
                    )}

                    <DashboardActions
                        canOpenNodes={canOpenNodes}
                        canOpenAssets={canOpenAssets}
                        canOpenUsers={canOpenUsers}
                        navigate={navigate}
                    />

                    <section className="dashboard-grid">
                        <AccessSummaryPanel
                            canOpenNodes={canOpenNodes}
                            canOpenAssets={canOpenAssets}
                            canOpenUsers={canOpenUsers}
                            role={role}
                        />
                        <AttentionSummaryPanel
                            canOpenNodes={canOpenNodes}
                            canOpenAssets={canOpenAssets}
                            summary={summary}
                        />
                    </section>
                </>
            )}
        </main>
    );
}
