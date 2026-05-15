/**
 * @file NodeRoleBadge.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Role badge for node role display.
 * @version 1.0.0
 * @date 2026-05-11

 * @Copyright (c) 2026
 */

import {
    formatNodeRole,
    formatNodeRoleTone,
} from "../../utils/nodeFormatters";

export default function NodeRoleBadge({ role }) {
    const tone = formatNodeRoleTone(role);

    return (
        <span className={`status-badge ${tone}`}>
            {formatNodeRole(role)}
        </span>
    );
}