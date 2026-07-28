/**
 * @file Sidebar.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-12

 * @Copyright (c) 2026
 */

import {
    Activity,
    AlertTriangle,
    Boxes,
    LayoutDashboard,
    RadioTower,
} from "lucide-react";

const MENU_ITEMS = [
    { key: "dashboard", label: "Dashboard", icon: LayoutDashboard },
    { key: "assets", label: "Assets", icon: Boxes },
    { key: "nodes", label: "Nodes", icon: RadioTower },
    { key: "alerts", label: "Alerts", icon: AlertTriangle },
    { key: "activity", label: "Activity", icon: Activity },
];

export function Sidebar({ activePage, setActivePage }) {
    return (
        <aside className="w-72 border-r border-slate-800 bg-slate-950 p-5">
            <div className="mb-8">
                <h1 className="text-xl font-bold tracking-tight">
                    Asset Monitor
                </h1>
                <p className="mt-1 text-sm text-slate-400">
                    Hospital tracking system
                </p>
            </div>

            <nav className="space-y-2">
                {MENU_ITEMS.map((item) => {
                    const Icon = item.icon;
                    const isActive = activePage === item.key;

                    return (
                        <button
                            key={item.key}
                            type="button"
                            onClick={() => setActivePage(item.key)}
                            className={[
                                "flex w-full items-center gap-3 rounded-2xl px-4 py-3 text-left text-sm transition",
                                isActive
                                    ? "bg-cyan-500 text-slate-950"
                                    : "text-slate-300 hover:bg-slate-900",
                            ].join(" ")}
                        >
                            <Icon size={18} />
                            {item.label}
                        </button>
                    );
                })}
            </nav>
        </aside>
    );
}