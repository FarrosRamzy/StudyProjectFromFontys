/**
 * @file useDeregisterTagSelection.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-11

 * @Copyright (c) 2026
 */

import { useEffect, useMemo, useState } from "react";

export function useDeregisterTagSelection({
    assets = [],
    latestScan,
    scannedTagId,
    deregisterTagId,
    setDeregisterTagId,
}) {
    const [ignoreScannedTag, setIgnoreScannedTag] = useState(false);
    const effectiveTagId = deregisterTagId || (!ignoreScannedTag ? scannedTagId : "") || "";
    const selectedAsset = useMemo(() => {
        if (!effectiveTagId) {
            return null;
        }
        return assets.find((asset) => asset.tag_id === effectiveTagId) || null;
    }, [assets, effectiveTagId]);

    useEffect(() => {
        setIgnoreScannedTag(false);
    }, [latestScan?.received_at]);

    function handleUseScannedTag() {
        if (!scannedTagId) {
            return null;
        }

        setDeregisterTagId(scannedTagId);
        setIgnoreScannedTag(false);
    }

    function handleClearTag() {
        setDeregisterTagId("");
        setIgnoreScannedTag(true);
    }

    return {
        effectiveTagId,
        selectedAsset,
        handleUseScannedTag,
        handleClearTag,
    };
}