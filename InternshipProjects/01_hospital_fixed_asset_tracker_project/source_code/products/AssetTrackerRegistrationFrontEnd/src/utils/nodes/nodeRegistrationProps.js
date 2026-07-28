/**
 * @file nodeRegistrationProps.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


export function buildAssignNodeFormProps({ form, actions, handlers, mqtt }) {
    const selectedId = form.selectedNode?.device_id;

    return {
        selectedNode: form.selectedNode,
        alias: form.alias,
        setAlias: form.setAlias,
        role: form.role,
        setRole: form.setRole,
        roomName: form.roomName,
        setRoomName: form.setRoomName,
        mqttSettings: mqtt.settings,
        mqttSettingsLoading: mqtt.loading,
        assigning: actions.assigning,
        unassigning: actions.unassigningNodeId === selectedId,
        deleting: actions.deletingNodeId === selectedId,
        onAssignSubmit: handlers.handleAssignSubmit,
        onUnassign: handlers.handleUnassignSelectedNode,
        onDelete: handlers.handleDeleteSelectedNode,
        onCancel: handlers.handleCancelForm,
    };
}
