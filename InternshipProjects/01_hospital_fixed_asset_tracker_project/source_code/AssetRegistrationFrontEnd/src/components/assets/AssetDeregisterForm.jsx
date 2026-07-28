/**
 * @file AssetDeregisterForm.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-05

 * @Copyright (c) 2026
 */

import { forwardRef } from "react";
import { getNodeLabel } from "../../utils/nodeHelpers";
import { useDeregisterTagSelection } from "../../hooks/useDeregisterTagSelection";

const AssetDeregisterForm = forwardRef(function AssetDeregisterForm(
  {
    assets = [],
    registrationNodes,

    latestScan,
    scannedTagId,
    deregisterTagId,
    setDeregisterTagId,

    deregisterNodeId,
    setDeregisterNodeId,

    deregisterReason,
    setDeregisterReason,

    saving,
    onSubmit,
  },
  ref
) {
  const {
    effectiveTagId,
    selectedAsset,
    handleUseScannedTag,
    handleClearTag,
  } = useDeregisterTagSelection({
    assets,
    latestScan,
    scannedTagId,
    deregisterTagId,
    setDeregisterTagId,
  });

  return (
    <div ref={ref}>
      <form className="asset-form" onSubmit={onSubmit}>
        <div className="section-header">
          <h2>Deregister Asset</h2>
          <p>
            Scan a registered RFID tag or choose an asset from the table using
            the Deregister button.
          </p>
        </div>

        <div className="form-grid">
          <div className="form-field">
            <span>Asset Tag</span>

            <div
              className={`tag-id-card deregister-tag-card ${effectiveTagId ? "has-tag" : "empty-tag"
                }`}
            >
              <div className="tag-id-card-header">
                <strong>
                  {effectiveTagId
                    ? "Asset Tag Selected"
                    : "No Asset Tag Selected"}
                </strong>

                <small>
                  {effectiveTagId
                    ? "Ready to deregister"
                    : "Scan a tag or click Deregister from the table"}
                </small>
              </div>

              <div className="tag-id-value tag-id-value-with-name">
                <span> {effectiveTagId
                  ? effectiveTagId
                  : "Waiting for tag ..."}
                </span>
                {effectiveTagId && (
                  <strong>
                    {selectedAsset?.item_name || "unknown asset"}
                  </strong>
                )}
              </div>
            </div>

            {scannedTagId && scannedTagId !== deregisterTagId && (
              <button
                type="button"
                className="small-button"
                onClick={handleUseScannedTag}
                disabled={saving}
              >
                Use latest scanned tag
              </button>
            )}

            {effectiveTagId && (
              <button
                type="button"
                className="small-button"
                onClick={handleClearTag}
                disabled={saving}
              >
                Clear selected tag
              </button>
            )}
          </div>

          <label className="form-field">
            <span>Registration Node</span>
            <select
              value={deregisterNodeId}
              onChange={(event) => setDeregisterNodeId(event.target.value)}
              disabled={saving}
            >
              <option value="">Select registration node</option>

              {registrationNodes.map((node) => (
                <option key={node.device_id} value={node.device_id}>
                  {getNodeLabel(node)}
                </option>
              ))}
            </select>
          </label>

          <label className="form-field">
            <span>Reason</span>
            <input
              value={deregisterReason}
              onChange={(event) => setDeregisterReason(event.target.value)}
              placeholder="Example: Asset retired"
              disabled={saving}
            />
          </label>
        </div>

        <div className="form-actions">
          <button
            type="submit"
            className="danger-button"
            disabled={saving || !effectiveTagId || !deregisterNodeId}
          >
            {saving ? "Deregistering..." : "Deregister Asset"}
          </button>
        </div>
      </form>
    </div>
  );
});

export default AssetDeregisterForm;