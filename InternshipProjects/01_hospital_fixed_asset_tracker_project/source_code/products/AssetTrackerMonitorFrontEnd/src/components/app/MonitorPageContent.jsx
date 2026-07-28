/**
 * @file MonitorPageContent.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { ErrorBanner } from "../common/ErrorBanner.jsx";
import { LoadingState } from "../common/LoadingState.jsx";
import { MonitorDashboard } from "../../pages/MonitorDashboard.jsx";
import { AssetMonitor } from "../../pages/AssetMonitor.jsx";
import { NodeMonitor } from "../../pages/NodeMonitor.jsx";
import { AlertCenter } from "../../pages/AlertCenter.jsx";
import { ActivityLog } from "../../pages/ActivityLog.jsx";
import { APP_ROUTES } from "../../constants/appRoutes.js";

export function MonitorPageContent({
    activePage,
    data,
    loading,
    error,
    refreshAll,
    onNavigate,
}) {
    if (loading) {
        return <LoadingState message="Loading monitor data..." />;
    }

    if (error) {
        return (
            <ErrorBanner
                title="Unable to load monitor data"
                message={error}
                actionLabel="Retry"
                onAction={refreshAll}
            />
        );
    }

    const pageProps = { ...data, onRefresh: refreshAll };

    if (activePage === APP_ROUTES.ASSETS) {
        return <AssetMonitor {...pageProps} />;
    }

    if (activePage === APP_ROUTES.NODES) {
        return <NodeMonitor nodes={data.nodes} onRefresh={refreshAll} />;
    }

    if (activePage === APP_ROUTES.ALERTS) {
        return <AlertCenter {...pageProps} />;
    }

    if (activePage === APP_ROUTES.ACTIVITY) {
        return <ActivityLog {...data} />;
    }

    return <MonitorDashboard {...data} onNavigate={onNavigate} />;
}
