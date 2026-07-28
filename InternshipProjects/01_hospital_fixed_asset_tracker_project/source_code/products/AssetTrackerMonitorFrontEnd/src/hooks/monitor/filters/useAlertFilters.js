/**
 * @file useAlertFilters.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { useMemo, useState } from "react";
import { includesSearchKeyword } from "../../../utils/textFormat";

export function useAlertFilters(alerts = []) {
    const [search, setSearch] = useState("");
    const [severity, setSeverity] = useState("all");
    const [type, setType] = useState("all");

    const filteredAlerts = useMemo(() => alerts.filter((alert) => {
        const matchesSearch = includesSearchKeyword([
            alert.title, alert.message, alert.type, alert.severity,
            alert.asset?.item_name, alert.asset?.tag_id,
            alert.node?.device_id, alert.node?.alias,
        ], search);
        const matchesSeverity = severity === "all" || alert.severity === severity;
        const matchesType = type === "all" || alert.type === type;
        return matchesSearch && matchesSeverity && matchesType;
    }), [alerts, search, severity, type]);

    return { search, setSearch, severity, setSeverity, type, setType, filteredAlerts };
}
