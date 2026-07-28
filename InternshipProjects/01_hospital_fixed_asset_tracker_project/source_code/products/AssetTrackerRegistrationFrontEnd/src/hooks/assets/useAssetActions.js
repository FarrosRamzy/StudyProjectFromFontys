/**
 * @file useAssetActions.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-08

 * @Copyright (c) 2026
 */


import { useState } from "react";
import {
    registerAsset,
    deregisterAsset,
    deleteAsset,
} from "../../services/assetApi";

function upsertAssetByTagId(currentAssets, updatedAsset) {
    if (!updatedAsset?.tag_id) {
        return currentAssets;
    }

    const exists = currentAssets.some(
        (asset) => asset.tag_id === updatedAsset.tag_id
    );

    if (!exists) {
        return [updatedAsset, ...currentAssets];
    }

    return currentAssets.map((asset) =>
        asset.tag_id === updatedAsset.tag_id ? updatedAsset : asset
    );
}

export function useAssetActions({
    setAssets,
    setError,
    setSuccessMessage,
    refreshData,
}) {
    const [registering, setRegistering] = useState(false);
    const [deregistering, setDeregistering] = useState(false);
    const [deletingTagId, setDeletingTagId] = useState("");

    async function handleRegisterAsset(payload) {
        setRegistering(true);
        setError("");
        setSuccessMessage("");

        try {
            const result = await registerAsset(payload);

            if (result.asset) {
                setAssets((currentAssets) =>
                    upsertAssetByTagId(currentAssets, result.asset)
                );
            } else {
                await refreshData();
            }

            setSuccessMessage("Asset registered successfully.");
        } catch (err) {
            setError(err.message || "Failed to register asset.");
        } finally {
            setRegistering(false);
        }
    }

    async function handleDeregisterAsset(payload) {
        setDeregistering(true);
        setError("");
        setSuccessMessage("");

        try {
            const result = await deregisterAsset(payload);

            if (result.asset) {
                setAssets((currentAssets) =>
                    upsertAssetByTagId(currentAssets, result.asset)
                );
            } else {
                await refreshData();
            }

            setSuccessMessage("Asset deregistered successfully.");
        } catch (err) {
            setError(err.message || "Failed to deregister asset.");
        } finally {
            setDeregistering(false);
        }
    }

    async function handleDeleteAsset(tagId) {
        const confirmed = window.confirm(
            `Delete asset with tag ID "${tagId}"? This should only be done after deregistration.`
        );

        if (!confirmed) {
            return;
        }

        setDeletingTagId(tagId);
        setError("");
        setSuccessMessage("");

        try {
            const result = await deleteAsset(tagId);

            if (result.message === "asset_deleted") {
                setAssets((currentAssets) =>
                    currentAssets.filter((asset) => asset.tag_id !== tagId)
                );

                setSuccessMessage("Asset deleted successfully.");
                return;
            }

            setError(result.message || "Failed to delete asset.");
        } catch (err) {
            setError(err.message || "Failed to delete asset.");
        } finally {
            setDeletingTagId("");
        }
    }

    return {
        registering,
        deregistering,
        deletingTagId,
        handleRegisterAsset,
        handleDeregisterAsset,
        handleDeleteAsset,
    };
}