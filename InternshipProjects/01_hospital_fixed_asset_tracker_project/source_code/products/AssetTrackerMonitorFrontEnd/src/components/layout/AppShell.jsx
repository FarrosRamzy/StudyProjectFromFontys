/**
 * @file AppShell.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Main visual shell for the Hospital Asset Monitor app.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { APP_NAV_ITEMS } from "../../constants/appRoutes";

import { Topbar } from "./Topbar";

export function AppShell({
    activePage,
    onNavigate,
    user,
    wsStatus,
    onRefresh,
    onLogout,
    children,
}) {
    return (
        <main className="monitor-page">
            <div className="sticky-page-header">
                <Topbar
                    user={user}
                    wsStatus={wsStatus}
                    onRefresh={onRefresh}
                    onLogout={onLogout}
                />

                <nav
                    className="sticky-tabs-shell"
                    aria-label="Monitor pages"
                >
                    <div
                        className="monitor-tabs"
                        role="tablist"
                        aria-label="Monitor pages"
                    >
                        {APP_NAV_ITEMS.map((item) => (
                            <button
                                key={item.key}
                                type="button"
                                role="tab"
                                aria-selected={activePage === item.key}
                                className={`monitor-tab ${
                                    activePage === item.key ? "active" : ""
                                }`}
                                onClick={() => onNavigate?.(item.key)}
                                title={item.description}
                            >
                                {item.label}
                            </button>
                        ))}
                    </div>
                </nav>
            </div>

            <section className="hero">
                <div>
                    <p className="eyebrow">Realtime Hospital Asset Tracking</p>

                    <h1>Hospital Asset Monitor</h1>

                    <p>
                        Monitor asset locations, checkpoint node health,
                        movement requests, wrong-location warnings, and
                        unauthorized asset movement from one realtime dashboard.
                    </p>
                </div>

                <div className="hero-status-card">
                    <span>System Mode</span>
                    <strong>Live Monitor</strong>
                    <p>Backend, database, and WebSocket-driven asset tracking.</p>
                </div>
            </section>

            <section className="panel form-tabs-panel">
                <div className="form-tab-content">
                    {children}
                </div>
            </section>
        </main>
    );
}
