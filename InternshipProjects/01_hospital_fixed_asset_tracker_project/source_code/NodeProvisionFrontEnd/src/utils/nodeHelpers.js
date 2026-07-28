/**
 * @file nodeHelpers.js
 * @author Farros Ramzy (you@domain.com)
 * @description Helper functions for node identity, role, status, and backend-compatible payloads.
 * @version 1.0.0
 * @date 2026-05-11

 * @Copyright (c) 2026
 */

export {
    NODE_ROLES,
    NODE_ROLE_LABELS,
    NODE_STATUSES,
    NODE_STATUS_LABELS,
} from "./nodes/nodeConstants";

export {
    getNodeIdentity,
    getNodeAlias,
    getNodeDisplayName,
    getNodeHospitalId,
    getNodeHospitalName,
    getNodeRoomName,
    getNodeMqttHost,
    getNodeMqttPort,
    getNodeLocation,
    getNodeRole,
    getNodeStatus,
    isCheckpointNode,
    isRegistrationNode,
    isNodeProvisioned,
    isNodeOnline,
    isNodeOffline,
    isNodeDisabled,
    isNodeDiscovered,
    canAssignNode,
    canEditNode,
    canUnassignNode,
    canDeleteNode,
} from "./nodes/nodeAccessors";

export {
    normalizeNodeRole,
    normalizeNodeStatus,
    normalizeNode,
    normalizeNodes,
} from "./nodes/nodeNormalizers";

export {
    hospitalNameToId,
    buildNodeAssignmentPayload,
} from "./nodes/nodePayloads";

export {
    isValidNodeAssignmentForm,
    validateNodeAssignmentForm,
    normalizeMqttPort,
} from "./nodes/nodeValidators";

export {
    upsertNode,
    removeNodeById,
} from "./nodes/nodeState";