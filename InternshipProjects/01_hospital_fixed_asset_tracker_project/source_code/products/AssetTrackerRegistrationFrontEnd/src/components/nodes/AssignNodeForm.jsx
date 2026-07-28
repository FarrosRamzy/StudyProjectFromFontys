/**
 * @file AssignNodeForm.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Form for assigning, editing, unassigning, or deleting a node.
 * @version 1.5.0
 * @date 2026-04-30

 * @Copyright (c) 2026
 */


import {
    canDeleteNode,
    canEditNode,
    canUnassignNode,
} from "../../utils/nodeHelpers";
import AssignNodeActions from "./assign/AssignNodeActions";
import AssignNodeFields from "./assign/AssignNodeFields";
import SelectedNodeCard from "./assign/SelectedNodeCard";

export default function AssignNodeForm(props) {
    const hasSelectedNode = Boolean(props.selectedNode?.device_id);
    const isEditMode = hasSelectedNode && canEditNode(props.selectedNode);
    const showUnassign = hasSelectedNode && canUnassignNode(props.selectedNode);
    const showDelete = hasSelectedNode && canDeleteNode(props.selectedNode);

    return (
        <section className="panel assignment-panel narrow-panel">
            <div className="section-header">
                <div>
                    <h2>{isEditMode ? "Edit Node" : "Assign Node"}</h2>
                    <p>Select a discovered node, assign its role, and bind it to a hospital location.</p>
                </div>
            </div>

            <SelectedNodeCard selectedNode={props.selectedNode} />

            <form className="asset-form" onSubmit={props.onAssignSubmit}>
                <AssignNodeFields {...props} />
                <AssignNodeActions
                    hasSelectedNode={hasSelectedNode}
                    isEditMode={isEditMode}
                    showUnassign={showUnassign}
                    showDelete={showDelete}
                    assigning={props.assigning}
                    unassigning={props.unassigning}
                    deleting={props.deleting}
                    onUnassign={props.onUnassign}
                    onDelete={props.onDelete}
                    onCancel={props.onCancel}
                />
            </form>
        </section>
    );
}
