/**
 * @file assetRegistrationProps.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


export function buildRegisterProps({ socket, formState, registrationNodes, checkpointNodes, assetActions, handlers }) {
    return {
        registrationNodes,
        checkpointNodes,
        selectedNodeId: socket.selectedNodeId,
        setSelectedNodeId: socket.setSelectedNodeId,
        initialNodeId: formState.initialNodeId,
        setInitialNodeId: formState.setInitialNodeId,
        tagId: socket.tagId,
        assetName: formState.assetName,
        setAssetName: formState.setAssetName,
        latestScan: socket.latestScan,
        saving: assetActions.registering,
        onSubmit: handlers.handleRegisterSubmit,
    };
}

export function buildDeregisterProps({ socket, formState, data, assetActions, handlers, registrationNodes, deregisterFormRef }) {
    return {
        ref: deregisterFormRef,
        assets: data.assets,
        registrationNodes,
        latestScan: socket.latestScan,
        scannedTagId: socket.tagId,
        deregisterTagId: formState.deregisterTagId,
        setDeregisterTagId: formState.setDeregisterTagId,
        deregisterNodeId: socket.deregisterNodeId,
        setDeregisterNodeId: socket.setDeregisterNodeId,
        deregisterReason: formState.deregisterReason,
        setDeregisterReason: formState.setDeregisterReason,
        saving: assetActions.deregistering,
        onSubmit: handlers.handleDeregisterSubmit,
    };
}

export function buildMovementProps({ socket, movementActions, registrationNodes }) {
    return {
        movementRequests: movementActions.movementRequests,
        loading: movementActions.loadingMovementRequests,
        actingMovementRequestId: movementActions.actingMovementRequestId,
        registrationNodes,
        registrationNodeId: socket.selectedNodeId,
        setRegistrationNodeId: socket.setSelectedNodeId,
        onRefresh: movementActions.refreshMovementRequests,
        onApprove: movementActions.handleApproveMovementRequest,
        onReject: movementActions.handleRejectMovementRequest,
    };
}
