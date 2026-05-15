/**
 * @file AlertsPage.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-12

 * @Copyright (c) 2026
 */

export function AlertsPage({ alerts }) {
    return (
        <div className="space-y-6">
            <div>
                <h1 className="text-2xl font-bold">Alerts</h1>
                <p className="mt-1 text-slate-400">
                    Unknown tags, inactive assets, and suspicious node activity.
                </p>
            </div>

            <div className="space-y-3">
                {alerts.map((alert) => (
                    <div
                        key={alert.id}
                        className="rounded-3xl border border-amber-500/20 bg-amber-500/10 p-5"
                    >
                        <div className="flex items-start justify-between gap-4">
                            <div>
                                <h2 className="font-semibold text-amber-100">
                                    {alert.title}
                                </h2>
                                <p className="mt-2 text-sm text-amber-100/80">
                                    {alert.description}
                                </p>
                            </div>

                            <span className="rounded-full bg-amber-500/20 px-3 py-1 text-xs text-amber-100">
                                {alert.type}
                            </span>
                        </div>

                        <p className="mt-3 text-xs text-amber-100/60">
                            {new Date(alert.createdAt).toLocaleString()}
                        </p>
                    </div>
                ))}

                {alerts.length === 0 && (
                    <div className="rounded-3xl border border-slate-800 bg-slate-900/70 p-8 text-center text-sm text-slate-500">
                        No alerts yet.
                    </div>
                )}
            </div>
        </div>
    );
}