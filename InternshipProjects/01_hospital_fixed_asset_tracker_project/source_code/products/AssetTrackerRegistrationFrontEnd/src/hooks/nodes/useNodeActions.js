/**
 * @file useNodeAction.js
 * @author Farros Ramzy (you@domain.com)
 * @description Node action handlers for assigning, provisioning, unassigning, and deleting nodes.
 * @version 1.0.0
 * @date 2026-05-11

 * @Copyright (c) 2026
 */


import { useAssignNodeAction } from "./actions/useAssignNodeAction";
import { useDeleteNodeAction } from "./actions/useDeleteNodeAction";
import { useIdentifyNodeAction } from "./actions/useIdentifyNodeAction";
import { useUnassignNodeAction } from "./actions/useUnassignNodeAction";

export function useNodeActions(options) {
    const assignAction = useAssignNodeAction(options);
    const unassignAction = useUnassignNodeAction(options);
    const deleteAction = useDeleteNodeAction(options);
    const identifyAction = useIdentifyNodeAction(options);

    return {
        assigning: assignAction.assigning,
        unassigningNodeId: unassignAction.unassigningNodeId,
        deletingNodeId: deleteAction.deletingNodeId,
        identifyingNodeId: identifyAction.identifyingNodeId,
        handleAssignNode: assignAction.handleAssignNode,
        handleUnassignNode: unassignAction.handleUnassignNode,
        handleDeleteNode: deleteAction.handleDeleteNode,
        handleIdentifyNode: identifyAction.handleIdentifyNode,
    };
}
