/**
 * @file DashboardPage.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-12

 * @Copyright (c) 2026
 */

import {
    AlertTriangle,
    Boxes,
    CheckCircle2,
    RadioTower,
} from "lucide-react";

function StatCard({ title, value, subtitle, icon: Icon }) {
    return (
        <div className="rounded-3xl border border-slate-800 bg-slate-900/70 p-5 shadow-xl shadow-black/10">
            <div className="flex items-start justify-between">
                <div>
                    <p className="text-sm text-slate-400">{title}</p>
                    <p className="mt-3 text-3xl font-bold">{value}</p>
                    <p className="mt-2 text-sm text-slate-500">{subtitle}</p>
                </div>

                <div className="rounded-2xl bg-slate-800 p-3">
                    <Icon size={22} />
                </div>
            </div>
        </div>
    );
}

export function DashboardPage({ assets, nodes, alerts, activity }) {
    const activeAssets = assets.filter((asset) => asset.status === "active");
    const onlineNodes = nodes.filter((node) => node.status === "ONLINE");
    const offlineNodes = nodes.filter((node) => node.status === "OFFLINE");

    return (
        <div className="space-y-6">
            <div>
                <h1 className="text-2xl font-bold">Dashboard</h1>
                <p className="mt-1 text-slate-400">
                    Live overview of hospital assets and RFID nodes.
                </p>
            </div>

            <div className="grid gap-4 md:grid-cols-2 xl:grid-cols-4">
                <StatCard
                    title="Registered Assets"
                    value={assets.length}
                    subtitle={`${activeAssets.length} active`}
                    icon={Boxes}
                />

                <StatCard
                    title="Online Nodes"
                    value={onlineNodes.length}
                    subtitle={`${offlineNodes.length} offline`}
                    icon={RadioTower}
                />

                <StatCard
                    title="Open Alerts"
                    value={alerts.length}
                    subtitle="Unknown tags and inactive assets"
                    icon={AlertTriangle}
                />

                <StatCard
                    title="System Status"
                    value={offlineNodes.length === 0 ? "Good" : "Check"}
                    subtitle={
                        offlineNodes.length === 0
                            ? "All nodes are healthy"
                            : "Some nodes need attention"
                    }
                    icon={CheckCircle2}
                />
            </div>

            <div className="grid gap-4 xl:grid-cols-2">
                <section className="rounded-3xl border border-slate-800 bg-slate-900/70 p-5">
                    <h2 className="text-lg font-semibold">Recent Activity</h2>

                    <div className="mt-4 space-y-3">
                        {activity.length === 0 ? (
                            <p className="text-sm text-slate-500">
                                No activity yet.
                            </p>
                        ) : (
                            activity.slice(0, 8).map((item) => (
                                <div
                                    key={item.id}
                                    className="rounded-2xl bg-slate-950/70 p-3"
                                >
                                    <p className="text-sm">{item.message}</p>
                                    <p className="mt-1 text-xs text-slate-500">
                                        {new Date(item.createdAt).toLocaleString()}
                                    </p>
                                </div>
                            ))
                        )}
                    </div>
                </section>

                <section className="rounded-3xl border border-slate-800 bg-slate-900/70 p-5">
                    <h2 className="text-lg font-semibold">System Health</h2>

                    <div className="mt-4 space-y-3">
                        {nodes.slice(0, 8).map((node) => (
                            <div
                                key={node.device_id}
                                className="flex items-center justify-between rounded-2xl bg-slate-950/70 p-3"
                            >
                                <div>
                                    <p className="font-medium">
                                        {node.alias || node.device_id}
                                    </p>
                                    <p className="text-sm text-slate-500">
                                        {node.room_name || "No room assigned"}
                                    </p>
                                </div>

                                <span className="rounded-full bg-slate-800 px-3 py-1 text-xs">
                                    {node.status || "UNKNOWN"}
                                </span>
                            </div>
                        ))}

                        {nodes.length === 0 && (
                            <p className="text-sm text-slate-500">
                                No nodes registered.
                            </p>
                        )}
                    </div>
                </section>
            </div>
        </div>
    );
}