/**
 * @file MovementRequestReasonField.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


export function MovementRequestReasonField({ reason, setReason, disabled }) {
    return (
        <label className="field">
            <span>Movement reason<strong className="required-marker"> *</strong></span>
            <textarea
                value={reason}
                disabled={disabled}
                onChange={(event) => setReason(event.target.value)}
                placeholder="Example: Needed for patient care in ICU Room 2"
                rows={4}
            />
        </label>
    );
}
