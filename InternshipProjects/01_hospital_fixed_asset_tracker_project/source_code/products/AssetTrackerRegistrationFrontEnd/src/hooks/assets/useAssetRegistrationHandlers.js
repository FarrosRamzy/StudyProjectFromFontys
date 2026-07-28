/**
 * @file useAssetRegistrationHandlers.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-08

 * @Copyright (c) 2026
 */


import { isNodeOnline } from "../../utils/nodeHelpers";

export function useAssetRegistrationHandlers({
    tagId,
    assetName,
    selectedNodeId,
    initialNodeId,
    registrationNodes,
    checkpointNodes,
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
}) {
    async function handleRegisterSubmit(event) {
        event.preventDefault();

        const cleanTagId = String(tagId || "").trim();
        const cleanAssetName = String(assetName || "").trim();
        const cleanInitialNodeId = String(initialNodeId || "").trim();

        const selectedRegistrationNode = registrationNodes.find(
            (node) => node.device_id === selectedNodeId
        );

        if (!selectedRegistrationNode || !isNodeOnline(selectedRegistrationNode)) {
            alert("The selected registration node is offline. Please choose an online registration node.");
            return;
        }

        const selectedInitialNode = checkpointNodes.find(
            (node) => node.device_id === cleanInitialNodeId
        );

        const initialRoomName = String(selectedInitialNode?.room_name || "").trim();

        if (
            !cleanTagId ||
            !cleanAssetName ||
            !selectedNodeId ||
            !cleanInitialNodeId ||
            !initialRoomName
        ) {
            return;
        }

        await handleRegisterAsset({
            tag_id: cleanTagId,
            item_name: cleanAssetName,
            registration_node_id: selectedNodeId,
            initial_room_name: initialRoomName,
            initial_node_id: cleanInitialNodeId,
        });

        resetRegisterForm();
    }

    async function handleDeregisterSubmit(event) {
        event.preventDefault();

        const cleanTagId = String(deregisterTagId || tagId || "").trim();
        const cleanReason = String(deregisterReason || "").trim();

        const selectedDeregisterNode = registrationNodes.find(
            (node) => node.device_id === deregisterNodeId
        );

        if (!selectedDeregisterNode || !isNodeOnline(selectedDeregisterNode)) {
            alert("The selected registration node is offline. Please choose an online registration node.");
            return;
        }

        if (!cleanTagId || !deregisterNodeId) {
            return;
        }

        if (!cleanReason) {
            alert("Please enter a deregistration reason.");
            return;
        }

        const confirmed = window.confirm(
            `Deregister asset with tag ID "${cleanTagId}"?\n\nThis asset will no longer be tracked as active.`
        );

        if (!confirmed) {
            return;
        }

        await handleDeregisterAsset({
            tag_id: cleanTagId,
            registration_node_id: deregisterNodeId,
            reason: cleanReason,
        });

        resetDeregisterForm();
    }

    function handleUseForDeregister(asset) {
        if (!asset?.tag_id) {
            return;
        }

        setDeregisterTagId(asset.tag_id);

        if (!deregisterNodeId && selectedNodeId) {
            setDeregisterNodeId(selectedNodeId);
        }

        setActiveFormTab?.("deregister");

        setTimeout(() => {
            deregisterFormRef.current?.scrollIntoView({
                behavior: "smooth",
                block: "start",
            });
        }, 50);
    }

    async function handleDeleteAssetFromTable(asset) {
        if (!asset?.tag_id) {
            return;
        }

        await handleDeleteAsset(asset.tag_id);
    }

    return {
        handleRegisterSubmit,
        handleDeregisterSubmit,
        handleUseForDeregister,
        handleDeleteAssetFromTable,
    };
}
