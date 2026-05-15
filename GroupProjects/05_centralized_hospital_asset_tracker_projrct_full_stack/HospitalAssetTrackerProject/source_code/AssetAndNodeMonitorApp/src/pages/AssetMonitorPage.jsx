/**
 * @file AssetMonitorPage.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-12

 * @Copyright (c) 2026
 */

import { useMemo, useState } from "react";

export function AssetMonitorPage({ assets }) {
    const [search, setSearch] = useState("");

    const filteredAssets = useMemo(() => {
        const keyword = search.trim().toLowerCase();

        if (!keyword) {
            return assets;
        }

        return assets.filter((asset) => {
            return [
                asset.item_name,
                asset.tag_id,
                asset.status,
                asset.hospital_name,
                asset.last_room_name,
                asset.last_device_id,
            ]
                .filter(Boolean)
                .some((value) => String(value).toLowerCase().includes(keyword));
        });
    }, [assets, search]);

    return (
        <div className="space-y-6">
            <div className="flex flex-col gap-4 md:flex-row md:items-end md:justify-between">
                <div>
                    <h1 className="text-2xl font-bold">Asset Monitor</h1>
                    <p className="mt-1 text-slate-400">
                        Track registered assets by RFID tag, room, and latest checkpoint.
                    </p>
                </div>

                <input
                    value={search}
                    onChange={(event) => setSearch(event.target.value)}
                    placeholder="Search asset, tag, room..."
                    className="w-full rounded-2xl border border-slate-800 bg-slate-950 px-4 py-3 text-sm outline-none focus:border-cyan-500 md:w-80"
                />
            </div>

            <div className="overflow-hidden rounded-3xl border border-slate-800 bg-slate-900/70">
                <table className="w-full text-left text-sm">
                    <thead className="border-b border-slate-800 bg-slate-950/70 text-slate-400">
                        <tr>
                            <th className="px-4 py-3">Asset</th>
                            <th className="px-4 py-3">Tag ID</th>
                            <th className="px-4 py-3">Status</th>
                            <th className="px-4 py-3">Last Room</th>
                            <th className="px-4 py-3">Last Node</th>
                            <th className="px-4 py-3">Last Seen</th>
                        </tr>
                    </thead>

                    <tbody>
                        {filteredAssets.map((asset) => (
                            <tr
                                key={asset.tag_id}
                                className="border-b border-slate-800/70 last:border-0"
                            >
                                <td className="px-4 py-4 font-medium">
                                    {asset.item_name || "Unnamed asset"}
                                </td>

                                <td className="px-4 py-4 font-mono text-xs text-slate-400">
                                    {asset.tag_id}
                                </td>

                                <td className="px-4 py-4">
                                    <span className="rounded-full bg-slate-800 px-3 py-1 text-xs">
                                        {asset.status || "unknown"}
                                    </span>
                                </td>

                                <td className="px-4 py-4">
                                    {asset.last_room_name || "-"}
                                </td>

                                <td className="px-4 py-4 font-mono text-xs text-slate-400">
                                    {asset.last_device_id || asset.last_node_id || "-"}
                                </td>

                                <td className="px-4 py-4 text-slate-400">
                                    {asset.last_seen_at
                                        ? new Date(asset.last_seen_at).toLocaleString()
                                        : "-"}
                                </td>
                            </tr>
                        ))}
                    </tbody>
                </table>

                {filteredAssets.length === 0 && (
                    <div className="p-8 text-center text-sm text-slate-500">
                        No assets found.
                    </div>
                )}
            </div>
        </div>
    );
}