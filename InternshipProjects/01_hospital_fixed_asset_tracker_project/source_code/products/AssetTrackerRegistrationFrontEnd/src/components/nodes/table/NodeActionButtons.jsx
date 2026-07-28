/**
 * @file NodeActionButtons.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


export default function NodeActionButtons({
    deviceId,
    actionLabel,
    isSelected,
    showBlinkButton,
    canIdentify,
    isIdentifying,
    isOffline,
    isDisabled,
    onIdentifyNode,
    onSelectNode,
    node,
}) {
    return (
        <div className="node-action-buttons">
            {showBlinkButton && (
                <button
                    type="button"
                    className="node-action-button node-action-button-secondary"
                    disabled={!canIdentify || isIdentifying}
                    title={getBlinkTitle({ isOffline, isDisabled })}
                    onClick={() => onIdentifyNode?.(deviceId)}
                >
                    {isIdentifying ? "Blinking..." : "Blink"}
                </button>
            )}

            <button
                type="button"
                className={
                    isSelected
                        ? "node-action-button node-action-button-selected"
                        : "node-action-button node-action-button-primary"
                }
                onClick={() => onSelectNode(node)}
            >
                {isSelected ? "Close" : actionLabel}
            </button>
        </div>
    );
}

function getBlinkTitle({ isOffline, isDisabled }) {
    if (isOffline) {
        return "This node is offline. Blink is unavailable.";
    }

    if (isDisabled) {
        return "This node is disabled. Blink is unavailable.";
    }

    return "Ask this physical node to blink";
}
