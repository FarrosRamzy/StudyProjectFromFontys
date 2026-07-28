/**
 * @file NodeRegistration.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Main page for registering, assigning, provisioning, and monitoring nodes.
 * @version 1.0.0
 * @date 2026-05-11

 * @Copyright (c) 2026
 */


import AssignNodeForm from "../components/nodes/AssignNodeForm";
import ConnectionStatus from "../components/common/ConnectionStatus";
import MessageBanner from "../components/common/MessageBanner";
import NodeTable from "../components/nodes/NodeTable";
import NodeToolbar from "../components/nodes/NodeToolbar";
import RegistrationModuleNav from "../components/common/RegistrationModuleNav";
import RegistrationTopbar from "../components/common/RegistrationTopbar";
import { useAuth } from "../context/AuthContext";
import { useNodeActions } from "../hooks/nodes/useNodeActions";
import { useNodeRegistrationAutoScroll } from "../hooks/nodes/useNodeRegistrationAutoScroll";
import { useNodeRegistrationData } from "../hooks/nodes/useNodeRegistrationData";
import { useNodeRegistrationFormState } from "../hooks/nodes/useNodeRegistrationFormState";
import { useNodeRegistrationHandlers } from "../hooks/nodes/useNodeRegistrationHandlers";
import { useNodeRegistrationSocket } from "../hooks/nodes/useNodeRegistrationSocket";
import { useNodeWarningScroll } from "../hooks/nodes/useNodeWarningScroll";
import { useAuthActions } from "../hooks/useAuthAction";
import { useMqttSettings } from "../hooks/settings/useMqttSettings";
import { buildAssignNodeFormProps } from "../utils/nodes/nodeRegistrationProps";

export default function NodeRegistration() {
    const { user } = useAuth();
    const { handleLogout } = useAuthActions();
    const data = useNodeRegistrationData();
    const socket = useNodeRegistrationSocket({
        setNodes: data.setNodes,
        setError: data.setError,
        setSuccessMessage: data.setSuccessMessage,
    });
    const form = useNodeRegistrationFormState();
    const mqtt = useMqttSettings();
    const { assignFormRef } = useNodeRegistrationAutoScroll(form.selectedNode);
    const messageBannerRef = useNodeWarningScroll(data.error);
    const actions = useNodeActions({
        setNodes: data.setNodes,
        setError: data.setError,
        setSuccessMessage: data.setSuccessMessage,
        refreshData: data.refreshData,
    });
    const handlers = useNodeRegistrationHandlers({
        ...form,
        setError: data.setError,
        setSuccessMessage: data.setSuccessMessage,
        handleAssignNode: actions.handleAssignNode,
        handleUnassignNode: actions.handleUnassignNode,
        handleDeleteNode: actions.handleDeleteNode,
        mqttSettings: mqtt.settings,
    });

    return (
        <main className="app-shell">
            <div className="sticky-page-header">
                <RegistrationTopbar
                    user={user}
                    subtitle="Node Provisioning Console"
                    onRefresh={() => {
                        data.refreshData();
                        mqtt.reloadSettings();
                    }}
                    onLogout={handleLogout}
                />
                <RegistrationModuleNav role={user?.role} />
            </div>

            <section className="page-hero">
                <div className="hero-main">
                    <p className="eyebrow">Hospital Asset Tracker</p>
                    <h1>Node Registration</h1>
                    <p className="hero-copy">
                        Register discovered RFID nodes, assign them as registration desks or checkpoint nodes,
                        and monitor their connection state in real time.
                    </p>
                </div>
                <ConnectionStatus status={socket.wsStatus} />
            </section>

            <MessageBanner ref={messageBannerRef} error={data.error || mqtt.error} successMessage={data.successMessage} />
            <NodeToolbar nodes={data.nodes} />
            <NodeTable
                nodes={data.nodes}
                loading={data.loading}
                selectedNode={form.selectedNode}
                onSelectNode={handlers.handleSelectNode}
                identifyingNodeId={actions.identifyingNodeId}
                onIdentifyNode={actions.handleIdentifyNode}
            />

            {form.selectedNode && (
                <section ref={assignFormRef} className="assign-form-scroll-target">
                    <AssignNodeForm {...buildAssignNodeFormProps({ form, actions, handlers, mqtt })} />
                </section>
            )}
        </main>
    );
}
