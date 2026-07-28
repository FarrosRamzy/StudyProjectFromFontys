/**
 * @file ActivityLog.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Realtime activity log page.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { useMemo, useState } from "react";
import { ActivityTable } from "../components/activity/ActivityTable";
import { includesSearchKeyword } from "../utils/textFormat";

export function ActivityLog({ activity = [], assets = [], nodes = [] }) {
    const [search, setSearch] = useState("");
    const sortedActivity = useMemo(() => {
        return activity
            .filter((item) => includesSearchKeyword([
                item.type, item.message, item.payload?.tag_id,
                item.payload?.item_name, item.payload?.device_id,
                item.payload?.node_id, item.payload?.room_name,
            ], search))
            .sort((a, b) => new Date(b.createdAt || 0) - new Date(a.createdAt || 0));
    }, [activity, search]);

    return (
        <div>
            <div className="section-header">
                <div><h2>Activity Log</h2><p>Realtime system events received by the monitor app.</p></div>
                <div className="status-badge neutral">{activity.length} events</div>
            </div>
            <div className="monitor-toolbar">
                <input
                    className="monitor-search"
                    value={search}
                    onChange={(event) => setSearch(event.target.value)}
                    placeholder="Search activity..."
                />
            </div>
            <ActivityTable activity={sortedActivity} assets={assets} nodes={nodes} />
        </div>
    );
}
