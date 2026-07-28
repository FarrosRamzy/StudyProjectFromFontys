/**
 * @file AssignNodeActions.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


export default function AssignNodeActions({
    hasSelectedNode,
    isEditMode,
    showUnassign,
    showDelete,
    assigning,
    unassigning,
    deleting,
    onUnassign,
    onDelete,
    onCancel,
}) {
    return (
        <div className="form-actions">
            <button type="submit" className="primary-button" disabled={!hasSelectedNode || assigning}>
                {assigning ? "Saving..." : isEditMode ? "Save Changes" : "Assign Node"}
            </button>

            {showUnassign && (
                <button type="button" className="danger-button" disabled={unassigning} onClick={onUnassign}>
                    {unassigning ? "Unassigning..." : "Unassign"}
                </button>
            )}

            {showDelete && (
                <button type="button" className="danger-button" disabled={deleting} onClick={onDelete}>
                    {deleting ? "Deleting..." : "Delete"}
                </button>
            )}

            <button type="button" className="ghost-button" onClick={onCancel}>
                Cancel
            </button>
        </div>
    );
}
