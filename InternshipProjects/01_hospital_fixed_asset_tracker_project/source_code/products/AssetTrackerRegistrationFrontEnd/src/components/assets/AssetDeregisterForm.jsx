/**
 * @file AssetDeregisterForm.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-05

 * @Copyright (c) 2026
 */


import { forwardRef } from "react";
import { isNodeOnline } from "../../utils/nodeHelpers";
import { useDeregisterTagSelection } from "../../hooks/assets/useDeregisterTagSelection";
import {
  DeregisterNodeSelect,
  DeregisterReasonField,
  DeregisterTagCard,
} from "./AssetDeregisterFields";

const AssetDeregisterForm = forwardRef(function AssetDeregisterForm(props, ref) {
  const tagSelection = useDeregisterTagSelection({
    assets: props.assets,
    latestScan: props.latestScan,
    scannedTagId: props.scannedTagId,
    deregisterTagId: props.deregisterTagId,
    setDeregisterTagId: props.setDeregisterTagId,
  });
  const selectedNode = props.registrationNodes.find(
    (node) => node.device_id === props.deregisterNodeId
  );
  const selectedNodeIsOnline = selectedNode ? isNodeOnline(selectedNode) : false;

  return (
    <div ref={ref}>
      <form className="asset-form" onSubmit={props.onSubmit}>
        <div className="section-header">
          <h2>Deregister Asset</h2>
          <p>Scan a registered RFID tag or choose an asset from the table using the Deregister button.</p>
        </div>

        <div className="form-grid">
          <DeregisterTagCard
            {...tagSelection}
            scannedTagId={props.scannedTagId}
            deregisterTagId={props.deregisterTagId}
            saving={props.saving}
          />
          <DeregisterNodeSelect
            registrationNodes={props.registrationNodes}
            deregisterNodeId={props.deregisterNodeId}
            setDeregisterNodeId={props.setDeregisterNodeId}
            saving={props.saving}
            selectedDeregisterNodeIsOnline={selectedNodeIsOnline}
          />
          <DeregisterReasonField
            deregisterReason={props.deregisterReason}
            setDeregisterReason={props.setDeregisterReason}
            saving={props.saving}
          />
        </div>

        <div className="form-actions">
          <button
            type="submit"
            className="danger-button"
            disabled={
              props.saving ||
              !tagSelection.effectiveTagId ||
              !props.deregisterNodeId ||
              !selectedNodeIsOnline ||
              !String(props.deregisterReason || "").trim()
            }
          >
            {props.saving ? "Deregistering..." : "Deregister Asset"}
          </button>
        </div>
      </form>
    </div>
  );
});

export default AssetDeregisterForm;
