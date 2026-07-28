/**
 * @file NodeStatusBadge.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Status badge for backend node statuses.
 * @version 1.0.0
 * @date 2026-05-11

 * @Copyright (c) 2026
 */

import {
  formatNodeStatus,
  formatNodeStatusTone,
} from "../../utils/nodeFormatters";

export default function NodeStatusBadge({ status }) {
  const tone = formatNodeStatusTone(status);

  return (
    <span className={`status-badge ${tone}`}>
      {formatNodeStatus(status)}
    </span>
  );
}