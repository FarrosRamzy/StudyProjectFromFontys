/**
 * @file AssetRegistration.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-04-30

 * @Copyright (c) 2026
 */


import { useCallback, useRef } from "react";

import { useAssetRegistrationTabs } from "../hooks/assets/useAssetRegistrationTabs";
import AssetRegistrationTabs from "../components/assets/registration/AssetRegistrationTabs";
import AssetTable from "../components/assets/AssetTable";
import ConnectionStatus from "../components/common/ConnectionStatus";
import MessageBanner from "../components/common/MessageBanner";
import RegistrationModuleNav from "../components/common/RegistrationModuleNav";
import RegistrationTopbar from "../components/common/RegistrationTopbar";
import { useAuth } from "../context/AuthContext";
import { useAssetActions } from "../hooks/assets/useAssetActions";
import { useAssetRegistrationData } from "../hooks/assets/useAssetRegistrationData";
import { useAssetRegistrationFormState } from "../hooks/assets/useAssetRegistrationFormState";
import { useAssetRegistrationHandlers } from "../hooks/assets/useAssetRegistrationHandlers";
import { useAssetRegistrationSocket } from "../hooks/assets/useAssetRegistrationSocket";
import { useCheckpointNodes } from "../hooks/assets/useCheckpointNodes";
import { useMovementRequestActions } from "../hooks/assets/useMovementRequestActions";
import { useRegistrationNodes } from "../hooks/assets/useRegistrationNodes";
import { useAuthActions } from "../hooks/useAuthAction";
import {
    buildDeregisterProps,
    buildMovementProps,
    buildRegisterProps,
} from "../utils/assets/assetRegistrationProps";

export default function AssetRegistration() {

    const { user } = useAuth();
    const { handleLogout } = useAuthActions();
    const { activeFormTab, handleAssetTabChange } = useAssetRegistrationTabs();

    const refreshMovementRequestsRef = useRef(null);
    const deregisterFormRef = useRef(null);

    const handleMovementRequestSocketChange = useCallback(() => {
        refreshMovementRequestsRef.current?.();
    }, []);

    const data = useAssetRegistrationData();
    const socket = useAssetRegistrationSocket({
        setAssets: data.setAssets,
        setError: data.setError,
        setSuccessMessage: data.setSuccessMessage,
        onMovementRequestChanged: handleMovementRequestSocketChange,
    });

    const assetActions = useAssetActions({
        setAssets: data.setAssets,
        setError: data.setError,
        setSuccessMessage: data.setSuccessMessage,
        refreshData: data.refreshData,
    });

    const registrationNodes = useRegistrationNodes(data.nodes);
    const checkpointNodes = useCheckpointNodes(data.nodes);
    const movementActions = useMovementRequestActions({
        registrationNodeId: socket.selectedNodeId,
        registrationNodes,
        setAssets: data.setAssets,
        setError: data.setError,
        setSuccessMessage: data.setSuccessMessage,
    });
    const formState = useAssetRegistrationFormState();

    refreshMovementRequestsRef.current = movementActions.refreshMovementRequests;

    const handlers = useAssetRegistrationHandlers({
        ...formState,
        ...assetActions,
        tagId: socket.tagId,
        selectedNodeId: socket.selectedNodeId,
        registrationNodes,
        checkpointNodes,
        deregisterNodeId: socket.deregisterNodeId,
        setDeregisterNodeId: socket.setDeregisterNodeId,
        deregisterFormRef,
        setActiveFormTab: handleAssetTabChange,
    });

    return (
        <main className="asset-registration-page">
            <div className="sticky-page-header">
                <RegistrationTopbar
                    user={user}
                    subtitle="Asset manager"
                    onRefresh={data.refreshData}
                    onLogout={handleLogout}
                />
                <RegistrationModuleNav role={user?.role} />
            </div>

            <header className="hero">
                <div>
                    <h1>Hospital Asset Registration</h1>
                    <p>Register and deregister RFID-tagged hospital assets using the registration desk node.</p>
                </div>
                <ConnectionStatus status={socket.wsStatus} />
            </header>

            <MessageBanner error={data.error} successMessage={data.successMessage} />
            <AssetRegistrationTabs
                activeFormTab={activeFormTab}
                setActiveFormTab={handleAssetTabChange}
                movementRequests={movementActions.movementRequests}
                registerProps={buildRegisterProps({ socket, formState, registrationNodes, checkpointNodes, assetActions, handlers })}
                deregisterProps={buildDeregisterProps({ socket, formState, data, assetActions, handlers, registrationNodes, deregisterFormRef })}
                movementProps={buildMovementProps({ socket, movementActions, registrationNodes })}
            />
            <AssetTable
                assets={data.assets}
                loading={data.loading}
                deletingTagId={assetActions.deletingTagId}
                onUseForDeregister={handlers.handleUseForDeregister}
                onDeleteAsset={handlers.handleDeleteAssetFromTable}
            />
        </main>
    );
}
