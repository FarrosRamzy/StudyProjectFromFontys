/**
 * @file AssetFlowBadge.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Badge for displaying backend asset flow_status values.
 * @version 1.0.0
 * @date 2026-05-22

 * @Copyright (c) 2026
 */


import { StatusBadge } from "../common/StatusBadge";

import {
    getAssetFlowLabel,
    getAssetFlowMeta,
    getAssetFlowTone,
} from "../../utils/flowStatus";

export function AssetFlowBadge({ flowStatus }) {
    const label = getAssetFlowLabel(flowStatus);
    const tone = getAssetFlowTone(flowStatus);
    const meta = getAssetFlowMeta(flowStatus);

    return (
        <StatusBadge
            tone={tone}
            title={meta.description || label}
        >
            {label}
        </StatusBadge>
    );
}
