/**
 * @file AssetRegistration.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-04-30

 * @Copyright (c) 2026
 */

import { useRef, useState } from "react";

import AssetRegisterForm from "../components/assets/AssetRegisterForm";
import AssetDeregisterForm from "../components/assets/AssetDeregisterForm";
import AssetTable from "../components/assets/AssetTable";
import MessageBanner from "../components/common/MessageBanner";
import ConnectionStatus from "../components/common/ConnectionStatus";

import { useAssetRegistrationData } from "../hooks/useAssetRegistrationData";
import { useAssetRegistrationSocket } from "../hooks/useAssetRegistrationSocket";
import { useAssetActions } from "../hooks/useAssetActions";
import { useAssetRegistrationFormState } from "../hooks/useAssetRegistrationFormState";
import { useAssetRegistrationHandlers } from "../hooks/useAssetRegistrationHandlers";
import { useRegistrationNodes } from "../hooks/useRegistrationNodes";

export default function AssetRegistration() {


    const {
        assets,
        setAssets,
        nodes,
        loading,
        error,
        setError,
        successMessage,
        setSuccessMessage,
        refreshData,
    } = useAssetRegistrationData();

    const {
        wsStatus,
        latestScan,
        tagId,
        setTagId,
        selectedNodeId,
        setSelectedNodeId,
        deregisterNodeId,
        setDeregisterNodeId,
    } = useAssetRegistrationSocket({
        setAssets,
        setError,
        setSuccessMessage,
    });

    const {
        registering,
        deregistering,
        deletingTagId,
        handleRegisterAsset,
        handleDeregisterAsset,
        handleDeleteAsset,
    } = useAssetActions({
        setAssets,
        setError,
        setSuccessMessage,
        refreshData,
    });

    const {
        assetName,
        setAssetName,
        deregisterTagId,
        setDeregisterTagId,
        deregisterReason,
        setDeregisterReason,
        resetRegisterForm,
        resetDeregisterForm,
    } = useAssetRegistrationFormState();

    const registrationNodes = useRegistrationNodes(nodes);
    const deregisterFormRef = useRef(null);
    const [activeFormTab, setActiveFormTab] = useState("register");

    const {
        handleRegisterSubmit,
        handleDeregisterSubmit,
        handleUseForDeregister,
        handleDeleteAssetFromTable,
    } = useAssetRegistrationHandlers({
        tagId,
        assetName,
        selectedNodeId,
        resetRegisterForm,

        deregisterTagId,
        deregisterNodeId,
        deregisterReason,
        setDeregisterTagId,
        setDeregisterNodeId,
        resetDeregisterForm,

        deregisterFormRef,
        setActiveFormTab,

        handleRegisterAsset,
        handleDeregisterAsset,
        handleDeleteAsset,
    });

    return (
        <main className="app-page">
            <header className="hero">
                <div>
                    <h1>Hospital Asset Registration</h1>
                    <p>
                        Register and deregister RFID-tagged hospital assets using the
                        registration desk node.
                    </p>
                </div>

                <ConnectionStatus status={wsStatus} onRefresh={refreshData} />
            </header>

            <MessageBanner error={error} successMessage={successMessage} />

            <section className="panel form-tabs-panel">
                <div className="form-tabs" role="tablist" aria-label="Asset actions">
                    <button
                        type="button"
                        className={`form-tab ${activeFormTab === "register" ? "active" : ""}`}
                        onClick={() => setActiveFormTab("register")}
                    >
                        Register Asset
                    </button>

                    <button
                        type="button"
                        className={`form-tab form-tab-danger ${activeFormTab === "deregister" ? "active" : ""}`}
                        onClick={() => setActiveFormTab("deregister")}
                    >
                        Deregister Asset
                    </button>
                </div>

                <div className="form-tab-content">
                    {activeFormTab === "register" && (
                        <AssetRegisterForm
                            registrationNodes={registrationNodes}
                            selectedNodeId={selectedNodeId}
                            setSelectedNodeId={setSelectedNodeId}
                            tagId={tagId}
                            assetName={assetName}
                            setAssetName={setAssetName}
                            latestScan={latestScan}
                            saving={registering}
                            onSubmit={handleRegisterSubmit}
                        />
                    )}

                    {activeFormTab === "deregister" && (
                        <AssetDeregisterForm
                            ref={deregisterFormRef}
                            assets={assets}
                            registrationNodes={registrationNodes}
                            latestScan={latestScan}
                            scannedTagId={tagId}
                            deregisterTagId={deregisterTagId}
                            setDeregisterTagId={setDeregisterTagId}
                            deregisterNodeId={deregisterNodeId}
                            setDeregisterNodeId={setDeregisterNodeId}
                            deregisterReason={deregisterReason}
                            setDeregisterReason={setDeregisterReason}
                            saving={deregistering}
                            onSubmit={handleDeregisterSubmit}
                        />
                    )}
                </div>
            </section>

            <AssetTable
                assets={assets}
                loading={loading}
                deletingTagId={deletingTagId}
                onUseForDeregister={handleUseForDeregister}
                onDeleteAsset={handleDeleteAssetFromTable}
            />
        </main>
    );
}