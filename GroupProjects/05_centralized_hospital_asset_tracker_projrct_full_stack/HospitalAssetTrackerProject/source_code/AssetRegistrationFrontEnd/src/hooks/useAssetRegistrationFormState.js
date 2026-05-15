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
    const [deregisterTagId, setDeregisterTagId] = useState("");
    const [deregisterReason, setDeregisterReason] = useState("");

    function resetRegisterForm() {
        setAssetName("");
    }

    function resetDeregisterForm() {
        setDeregisterTagId("");
        setDeregisterReason("");
    }

    return {
        assetName,
        setAssetName,

        deregisterTagId,
        setDeregisterTagId,

        deregisterReason,
        setDeregisterReason,

        resetRegisterForm,
        resetDeregisterForm,
    };
}