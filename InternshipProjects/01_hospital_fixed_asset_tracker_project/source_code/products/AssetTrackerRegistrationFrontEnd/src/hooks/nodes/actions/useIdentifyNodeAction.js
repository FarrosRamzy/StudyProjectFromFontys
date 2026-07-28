/**
 * @file useIdentifyNodeAction.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import { useState } from "react";
import { identifyNode } from "../../../services/nodeApi";
import { upsertNode } from "../../../utils/nodeHelpers";
import { cleanDeviceId, getIdentifyError } from "./nodeActionGuards";

export function useIdentifyNodeAction({ setNodes, setError, setSuccessMessage }) {
    const [identifyingNodeId, setIdentifyingNodeId] = useState("");

    async function handleIdentifyNode(deviceId) {
        const cleanId = cleanDeviceId(deviceId);

        if (!cleanId) {
            setError("Cannot identify node because the device ID is missing.");
            return false;
        }

        setIdentifyingNodeId(cleanId);
        setError("");
        setSuccessMessage("");

        try {
            const result = await identifyNode(cleanId, { blink_count: 6, interval_ms: 150 });

            if (result?.node?.device_id) {
                setNodes((current) => upsertNode(current, result.node));
            }

            const friendlyError = getIdentifyError(result?.message);
            if (friendlyError) {
                setError(friendlyError);
                return false;
            }

            if (result?.message !== "blink_command_sent") {
                setError(result?.reason || result?.message || "Failed to send the Blink command.");
                return false;
            }

            setSuccessMessage(`Blink command sent to ${cleanId}.`);
            return true;
        } catch (err) {
            setError(err.message || "Failed to send the Blink command.");
            return false;
        } finally {
            setIdentifyingNodeId("");
        }
    }

    return { identifyingNodeId, handleIdentifyNode };
}
