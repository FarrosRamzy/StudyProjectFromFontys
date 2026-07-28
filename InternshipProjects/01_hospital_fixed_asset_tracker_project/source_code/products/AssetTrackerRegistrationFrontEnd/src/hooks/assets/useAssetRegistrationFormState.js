/**
 * @file useAssetRegistrationFormState.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-08

 * @Copyright (c) 2026
 */


import { useState } from "react";

export function useAssetRegistrationFormState() {
    const [assetName, setAssetName] = useState("");
    const [initialNodeId, setInitialNodeId] = useState("");
    const [deregisterTagId, setDeregisterTagId] = useState("");
    const [deregisterReason, setDeregisterReason] = useState("");

    function resetRegisterForm() {
        setAssetName("");
        setInitialNodeId("");
    }

    function resetDeregisterForm() {
        setDeregisterTagId("");
        setDeregisterReason("");
    }

    return {
        assetName,
        setAssetName,

        initialNodeId,
        setInitialNodeId,

        deregisterTagId,
        setDeregisterTagId,

        deregisterReason,
        setDeregisterReason,

        resetRegisterForm,
        resetDeregisterForm,
    };
}