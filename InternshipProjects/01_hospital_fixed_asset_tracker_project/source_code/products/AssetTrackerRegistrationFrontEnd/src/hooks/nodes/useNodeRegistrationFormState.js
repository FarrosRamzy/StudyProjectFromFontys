/**
 * @file useNodeRegistrationFormState.js
 * @author Farros Ramzy (you@domain.com)
 * @description Form state for assigning/provisioning a node.
 * @version 1.0.0
 * @date 2026-05-11

 * @Copyright (c) 2026
 */


import { useState } from "react";
import {
    NODE_ROLES,
    getNodeAlias,
    getNodeHospitalName,
    getNodeMqttHost,
    getNodeMqttPort,
    getNodeRoomName,
    getNodeRole,
} from "../../utils/nodeHelpers";

export function useNodeRegistrationFormState() {
    const [selectedNode, setSelectedNode] = useState(null);

    const [alias, setAlias] = useState("");
    const [role, setRole] = useState(NODE_ROLES.CHECKPOINT);
    const [hospitalName, setHospitalName] = useState("");
    const [roomName, setRoomName] = useState("");
    const [mqttHost, setMqttHost] = useState("");
    const [mqttPort, setMqttPort] = useState(1883);

    function fillFormFromNode(node) {
        setSelectedNode(node || null);

        setAlias(getNodeAlias(node));
        setRole(getNodeRole(node) || NODE_ROLES.CHECKPOINT);
        setHospitalName(getNodeHospitalName(node) === "-" ? "" : getNodeHospitalName(node));
        setRoomName(getNodeRoomName(node));
        setMqttHost(getNodeMqttHost(node));
        setMqttPort(getNodeMqttPort(node));
    }

    function resetForm() {
        setSelectedNode(null);

        setAlias("");
        setRole(NODE_ROLES.CHECKPOINT);
        setHospitalName("");
        setRoomName("");
        setMqttHost("");
        setMqttPort(1883);
    }

    return {
        selectedNode,
        setSelectedNode,
        alias,
        setAlias,
        role,
        setRole,
        hospitalName,
        setHospitalName,
        roomName,
        setRoomName,
        mqttHost,
        setMqttHost,
        mqttPort,
        setMqttPort,
        fillFormFromNode,
        resetForm,
    };
}