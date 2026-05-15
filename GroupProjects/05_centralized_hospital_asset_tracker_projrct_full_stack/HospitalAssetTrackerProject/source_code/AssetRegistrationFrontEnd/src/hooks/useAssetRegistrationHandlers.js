/**
 * @file useAssetRegistrationHandlers.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-08

 * @Copyright (c) 2026
 */

export function useAssetRegistrationHandlers({
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
}) {
    async function handleRegisterSubmit(event) {
        event.preventDefault();

        const cleanTagId = String(tagId || "").trim();
        const cleanAssetName = String(assetName || "").trim();

        if (!cleanTagId || !cleanAssetName || !selectedNodeId) {
            return;
        }

        await handleRegisterAsset({
            tag_id: cleanTagId,
            item_name: cleanAssetName,
            registration_node_id: selectedNodeId,
        });

        resetRegisterForm();
    }
    
    async function handleDeregisterSubmit(event) {
        event.preventDefault();

        const cleanTagId = String(deregisterTagId || tagId || "").trim();

        if (!cleanTagId || !deregisterNodeId) {
            return;
        }

        await handleDeregisterAsset({
            tag_id: cleanTagId,
            registration_node_id: deregisterNodeId,
            reason: deregisterReason,
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