/**
 * @file ActivityPage.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-12

 * @Copyright (c) 2026
 */

export function ActivityPage({ activity }) {
    return (
        <div className="space-y-6">
            <div>
                <h1 className="text-2xl font-bold">Activity Feed</h1>
                <p className="mt-1 text-slate-400">
                    Live movement and system events.
                </p>
            </div>

            <div className="rounded-3xl border border-slate-800 bg-slate-900/70 p-5">
                <div className="space-y-3">
                    {activity.map((item) => (
                        <div
                            key={item.id}
                            className="rounded-2xl bg-slate-950/70 p-4"
                        >
                            <div className="flex items-start justify-between gap-4">
                                <p className="text-sm">{item.message}</p>

                                <span className="rounded-full bg-slate-800 px-3 py-1 text-xs text-slate-400">
                                    {item.type}
                                </span>
                            </div>

                            <p className="mt-2 text-xs text-slate-500">
                                {new Date(item.createdAt).toLocaleString()}
                            </p>
                        </div>
                    ))}

                    {activity.length === 0 && (
                        <p className="text-center text-sm text-slate-500">
                            No activity yet.
                        </p>
                    )}
                </div>
            </div>
        </div>
    );
}