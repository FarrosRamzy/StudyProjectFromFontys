/**
 * @file useNodeRegistrationAutoScroll.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-19

 * @Copyright (c) 2026
 */


import { useEffect, useRef } from "react";

export function useNodeRegistrationAutoScroll(selectedNode) {
    const assignFormRef = useRef(null);

    useEffect(() => {
        if (!selectedNode || !assignFormRef.current) {
            return;
        }

        const scrollTimer = window.setTimeout(() => {
            assignFormRef.current?.scrollIntoView({
                behavior: "smooth",
                block: "start",
            });
        }, 80);

        return () => {
            window.clearTimeout(scrollTimer);
        };
    }, [selectedNode]);

    return {
        assignFormRef,
    };
}