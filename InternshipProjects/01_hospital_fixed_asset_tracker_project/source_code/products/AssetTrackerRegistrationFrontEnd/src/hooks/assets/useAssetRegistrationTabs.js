/**
 * @file useAssetRegistrationTabs.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import {
    useCallback,
    useEffect,
    useState,
} from "react";

import { useSearchParams } from "react-router-dom";

const VALID_ASSET_TABS = new Set([
    "register",
    "movement",
    "deregister",
]);

function getValidAssetTab(tabName) {
    const normalizedTab = String(tabName || "")
        .trim()
        .toLowerCase();

    if (VALID_ASSET_TABS.has(normalizedTab)) {
        return normalizedTab;
    }

    return "register";
}

export function useAssetRegistrationTabs() {
    const [searchParams, setSearchParams] = useSearchParams();

    const [activeFormTab, setActiveFormTab] = useState(() =>
        getValidAssetTab(searchParams.get("tab"))
    );

    useEffect(() => {
        setActiveFormTab(
            getValidAssetTab(searchParams.get("tab"))
        );
    }, [searchParams]);

    const handleAssetTabChange = useCallback(
        (nextTab) => {
            const validTab = getValidAssetTab(nextTab);

            setActiveFormTab(validTab);

            const nextParams = new URLSearchParams(
                searchParams
            );

            if (validTab === "register") {
                nextParams.delete("tab");
            } else {
                nextParams.set("tab", validTab);
            }

            setSearchParams(nextParams, {
                replace: true,
            });
        },
        [searchParams, setSearchParams]
    );

    return {
        activeFormTab,
        handleAssetTabChange,
    };
}