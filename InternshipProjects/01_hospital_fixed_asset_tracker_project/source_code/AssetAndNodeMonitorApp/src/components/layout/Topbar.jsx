/**
 * @file Topbar.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-12

 * @Copyright (c) 2026
 */

function getStatusClass(wsStatus) {
    if (wsStatus === "connected") {
        return "bg-emerald-500";
    }

    if (wsStatus === "error") {
        return "bg-red-500";
    }

    return "bg-amber-500";
}

export function Topbar({ wsStatus }) {
    return (
        <header className="flex items-center justify-between border-b border-slate-800 bg-slate-950/80 px-6 py-4">
            <div>
                <p className="text-sm text-slate-400">
                    Real-time fixed asset tracking
                </p>
                <h2 className="text-lg font-semibold">
                    Monitoring Console
                </h2>
            </div>

            <div className="flex items-center gap-2 rounded-full border border-slate-800 px-4 py-2 text-sm">
                <span className={`h-2.5 w-2.5 rounded-full ${getStatusClass(wsStatus)}`} />
                <span className="capitalize text-slate-300">
                    WebSocket {wsStatus}
                </span>
            </div>
        </header>
    );
}