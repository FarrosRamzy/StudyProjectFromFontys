/**
 * @file useAssetFilters.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { useMemo, useState } from "react";
import { includesSearchKeyword } from "../../../utils/textFormat";

export function useAssetFilters(assets = []) {
    const [search, setSearch] = useState("");
    const [flowStatus, setFlowStatus] = useState("all");
    const [assetStatus, setAssetStatus] = useState("all");

    const filteredAssets = useMemo(() => assets.filter((asset) => {
        const matchesSearch = includesSearchKeyword([
            asset.item_name, asset.tag_id, asset.status, asset.flow_status,
            asset.last_room_name, asset.assigned_room_name, asset.expected_room_name,
            asset.hospital_name, asset.last_device_id, asset.movement_note,
        ], search);
        const matchesFlow = flowStatus === "all" || asset.flow_status === flowStatus;
        const matchesStatus = assetStatus === "all" || asset.status === assetStatus;
        return matchesSearch && matchesFlow && matchesStatus;
    }), [assets, search, flowStatus, assetStatus]);

    return {
        search, setSearch, flowStatus, setFlowStatus,
        assetStatus, setAssetStatus, filteredAssets,
    };
}
