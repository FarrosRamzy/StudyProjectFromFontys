/**
 * @file AppLayout.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-12

 * @Copyright (c) 2026
 */

import { Sidebar } from "./Sidebar";
import { Topbar } from "./Topbar";

export function AppLayout({ activePage, setActivePage, wsStatus, children }) {
    return (
        <div className="min-h-screen bg-slate-950 text-slate-100">
            <div className="flex min-h-screen">
                <Sidebar activePage={activePage} setActivePage={setActivePage} />

                <main className="flex-1">
                    <Topbar wsStatus={wsStatus} />
                    <div className="p-6">
                        {children}
                    </div>
                </main>
            </div>
        </div>
    );
}