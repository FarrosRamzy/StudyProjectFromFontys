/**
 * @file NodeMonitorPage.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-12

 * @Copyright (c) 2026
 */

import { useMemo, useState } from "react";

export function NodeMonitorPage({ nodes }) {
    const [search, setSearch] = useState("");

    const filteredNodes = useMemo(() => {
        const keyword = search.trim().toLowerCase();

        if (!keyword) {
            return nodes;
        }

        return nodes.filter((node) => {
            return [
                node.device_id,
                node.alias,
                node.role,
                node.status,
                node.hospital_name,
                node.room_name,
            ]
                .filter(Boolean)
                .some((value) => String(value).toLowerCase().includes(keyword));
        });
    }, [nodes, search]);

    return (
        <div className="space-y-6">
            <div className="flex flex-col gap-4 md:flex-row md:items-end md:justify-between">
                <div>
                    <h1 className="text-2xl font-bold">Node Monitor</h1>
                    <p className="mt-1 text-slate-400">
                        Monitor checkpoint and registration nodes in real time.
                    </p>
                </div>

                <input
                    value={search}
                    onChange={(event) => setSearch(event.target.value)}
                    placeholder="Search node, room, status..."
                    className="w-full rounded-2xl border border-slate-800 bg-slate-950 px-4 py-3 text-sm outline-none focus:border-cyan-500 md:w-80"
                />
            </div>

            <div className="grid gap-4 md:grid-cols-2 xl:grid-cols-3">
                {filteredNodes.map((node) => (
                    <div
                        key={node.device_id}
                        className="rounded-3xl border border-slate-800 bg-slate-900/70 p-5"
                    >
                        <div className="flex items-start justify-between gap-4">
                            <div>
                                <h2 className="font-semibold">
                                    {node.alias || node.device_id}
                                </h2>
                                <p className="mt-1 font-mono text-xs text-slate-500">
                                    {node.device_id}
                                </p>
                            </div>

                            <span className="rounded-full bg-slate-800 px-3 py-1 text-xs">
                                {node.status || "UNKNOWN"}
                            </span>
                        </div>

                        <div className="mt-5 space-y-3 text-sm">
                            <InfoRow label="Role" value={node.role || "-"} />
                            <InfoRow label="Room" value={node.room_name || "-"} />
                            <InfoRow label="Hospital" value={node.hospital_name || "-"} />
                            <InfoRow label="Last Ping" value={formatDate(node.last_ping_at)} />
                            <InfoRow label="Last Event" value={formatDate(node.last_event_at)} />
                        </div>
                    </div>
                ))}

                {filteredNodes.length === 0 && (
                    <div className="rounded-3xl border border-slate-800 bg-slate-900/70 p-8 text-center text-sm text-slate-500">
                        No nodes found.
                    </div>
                )}
            </div>
        </div>
    );
}

function InfoRow({ label, value }) {
    return (
        <div className="flex justify-between gap-4">
            <span className="text-slate-500">{label}</span>
            <span className="text-right text-slate-200">{value}</span>
        </div>
    );
}

function formatDate(value) {
    if (!value) {
        return "-";
    }

    return new Date(value).toLocaleString();
}