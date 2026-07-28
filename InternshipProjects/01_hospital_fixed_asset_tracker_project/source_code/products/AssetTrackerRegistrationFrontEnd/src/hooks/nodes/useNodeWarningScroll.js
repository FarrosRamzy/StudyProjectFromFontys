/**
 * @file useNodeWarningScroll.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import { useEffect, useRef } from "react";

export function useNodeWarningScroll(error) {
    const messageBannerRef = useRef(null);

    useEffect(() => {
        const shouldScrollToWarning =
            error?.includes("Cannot reassign this node") ||
            error?.includes("Cannot unassign this node");

        if (shouldScrollToWarning) {
            messageBannerRef.current?.scrollIntoView({
                behavior: "smooth",
                block: "center",
            });
        }
    }, [error]);

    return messageBannerRef;
}
