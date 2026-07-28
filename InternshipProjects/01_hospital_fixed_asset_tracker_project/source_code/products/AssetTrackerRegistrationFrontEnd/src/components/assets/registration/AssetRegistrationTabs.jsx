/**
 * @file AssetRegistrationTabs.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import AssetDeregisterForm from "../AssetDeregisterForm";
import AssetRegisterForm from "../AssetRegisterForm";
import MovementRequestsTable from "../MovementRequestsTable";

export default function AssetRegistrationTabs({
    activeFormTab,
    setActiveFormTab,
    movementRequests,
    registerProps,
    deregisterProps,
    movementProps,
}) {
    return (
        <section className="panel form-tabs-panel">
            <div className="form-tabs" role="tablist" aria-label="Asset actions">
                <TabButton
                    active={activeFormTab === "register"}
                    onClick={() => setActiveFormTab("register")}
                >
                    Register Asset
                </TabButton>

                <TabButton
                    active={activeFormTab === "movement"}
                    onClick={() => setActiveFormTab("movement")}
                >
                    Movement Requests
                    {movementRequests.length > 0 && (
                        <span className="tab-count-badge">{movementRequests.length}</span>
                    )}
                </TabButton>

                <TabButton
                    danger
                    active={activeFormTab === "deregister"}
                    onClick={() => setActiveFormTab("deregister")}
                >
                    Deregister Asset
                </TabButton>
            </div>

            <div className="form-tab-content">
                {activeFormTab === "register" && <AssetRegisterForm {...registerProps} />}
                {activeFormTab === "deregister" && <AssetDeregisterForm {...deregisterProps} />}
                {activeFormTab === "movement" && <MovementRequestsTable {...movementProps} />}
            </div>
        </section>
    );
}

function TabButton({ active, danger = false, onClick, children }) {
    const className = [
        "form-tab",
        danger ? "form-tab-danger" : "",
        active ? "active" : "",
    ]
        .filter(Boolean)
        .join(" ");

    return (
        <button type="button" className={className} onClick={onClick}>
            {children}
        </button>
    );
}
