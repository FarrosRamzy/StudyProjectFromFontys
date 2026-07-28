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
import { useNodeRegistrationHandlers } from "../hooks/useNodeRegistrationHandlers";
import { useNodeRegistrationAutoScroll } from "../hooks/useNodeRegistrationAutoScroll";
import { useNodeActions } from "../hooks/useNodeActions";
import { useAuthActions } from "../hooks/useAuthAction";
import { useAuth } from "../context/AuthContext";

export default function NodeRegistration() {
    const { user } = useAuth();
    const { handleLogout } = useAuthActions();

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

    const { assignFormRef } = useNodeRegistrationAutoScroll(selectedNode);

    const {
        assigning, unassigningNodeId, deletingNodeId, identifyingNodeId, handleAssignNode,
        handleUnassignNode, handleDeleteNode, handleIdentifyNode,
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
            <header className="app-topbar">
                <div className="app-brand-lockup">
                    <span className="app-brand-mark">H</span>

                    <div>
                        <strong>Hospital Asset Tracker</strong>
                        <span>Node Provisioning Console</span>
                    </div>
                </div>

                <div className="topbar-user">
                    <div className="topbar-user-text">
                        <span>Signed in as</span>
                        <strong>{user?.full_name || "System Administrator"}</strong>
                    </div>

                    <span className="topbar-role-badge">
                        {user?.role || "admin"}
                    </span>

                    <button
                        type="button"
                        className="topbar-logout-button"
                        onClick={handleLogout}
                    >
                        Logout
                    </button>
                </div>
            </header>

            <section className="page-hero">
                <div className="hero-main">
                    <p className="eyebrow">Hospital Asset Tracker</p>
                    <h1>Node Registration</h1>
                    <p className="hero-copy">
                        Register discovered RFID nodes, assign them as registration desks
                        or checkpoint nodes, and monitor their connection state in real time.
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
                identifyingNodeId={identifyingNodeId}
                onIdentifyNode={handleIdentifyNode}
            />

            {selectedNode && (
                <section ref={assignFormRef} className="assign-form-scroll-target">
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
                </section>
            )}
        </main>
    );
}