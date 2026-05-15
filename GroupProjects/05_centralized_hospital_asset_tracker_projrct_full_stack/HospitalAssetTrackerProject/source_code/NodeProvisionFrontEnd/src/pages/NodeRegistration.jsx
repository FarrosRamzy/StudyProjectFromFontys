/**
 * @file NodeRegistration.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Main page for registering, assigning, provisioning, and monitoring nodes.
 * @version 1.0.0
 * @date 2026-05-11

 * @Copyright (c) 2026
 */

import NodeToolbar from "../components/nodes/NodeToolbar";
import AssignNodeForm from "../components/nodes/AssignNodeForm";
import NodeTable from "../components/nodes/NodeTable";

import ConnectionStatus from "../components/common/ConnectionStatus";
import MessageBanner from "../components/common/MessageBanner";

import { useNodeRegistrationData } from "../hooks/useNodeRegistrationData";
import { useNodeRegistrationSocket } from "../hooks/useNodeRegistrationSocket";
import { useNodeRegistrationFormState } from "../hooks/useNodeRegistrationFormState";
import { useNodeActions } from "../hooks/useNodeActions";
import { useNodeRegistrationHandlers } from "../hooks/useNodeRegistrationHandlers";

export default function NodeRegistration() {
    const {
        nodes, setNodes,
        loading,
        error, setError,
        successMessage, setSuccessMessage,
        refreshData,
    } = useNodeRegistrationData();

    const {
        wsStatus,
    } = useNodeRegistrationSocket({
        setNodes, setError, setSuccessMessage,
    });

    const {
        selectedNode, setSelectedNode,
        alias, setAlias,
        role, setRole,
        hospitalName, setHospitalName,
        roomName, setRoomName,
        mqttHost, setMqttHost,
        mqttPort, setMqttPort,
        fillFormFromNode, resetForm,
    } = useNodeRegistrationFormState();

    const {
        assigning,
        unassigningNodeId, deletingNodeId,
        handleAssignNode, handleUnassignNode, handleDeleteNode,
    } = useNodeActions({
        setNodes, setError, setSuccessMessage, refreshData,
    });

    const {
        handleSelectNode, handleCancelForm, handleAssignSubmit,
        handleUnassignSelectedNode, handleDeleteSelectedNode,
    } = useNodeRegistrationHandlers({
        selectedNode, setSelectedNode, fillFormFromNode,
        alias, role, hospitalName, roomName, mqttHost, mqttPort,
        resetForm, setError, setSuccessMessage,
        handleAssignNode, handleUnassignNode, handleDeleteNode,
    });

    return (
        <main className="app-shell">
            <section className="hero-section">
                <div>
                    <p className="eyebrow">Hospital Asset Tracker</p>
                    <h1>Node Registration</h1>
                    <p className="hero-copy">
                        Register discovered RFID nodes, assign them as
                        registration desks or checkpoint nodes, and monitor
                        their connection state in real time.
                    </p>
                </div>

                <ConnectionStatus
                    status={wsStatus}
                    onRefresh={refreshData}
                />
            </section>

            <MessageBanner
                error={error}
                successMessage={successMessage}
            />

            <NodeToolbar nodes={nodes} />

            <NodeTable
                nodes={nodes}
                loading={loading}
                selectedNode={selectedNode}
                onSelectNode={handleSelectNode}
            />

            {selectedNode && (
                <AssignNodeForm
                    selectedNode={selectedNode}
                    alias={alias}
                    setAlias={setAlias}
                    role={role}
                    setRole={setRole}
                    hospitalName={hospitalName}
                    setHospitalName={setHospitalName}
                    roomName={roomName}
                    setRoomName={setRoomName}
                    mqttHost={mqttHost}
                    setMqttHost={setMqttHost}
                    mqttPort={mqttPort}
                    setMqttPort={setMqttPort}
                    assigning={assigning}
                    unassigning={unassigningNodeId === selectedNode?.device_id}
                    deleting={deletingNodeId === selectedNode?.device_id}
                    onAssignSubmit={handleAssignSubmit}
                    onUnassign={handleUnassignSelectedNode}
                    onDelete={handleDeleteSelectedNode}
                    onCancel={handleCancelForm}
                />
            )}
        </main>
    );
}