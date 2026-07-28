/**
 * @file UserPasswordReset.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


export default function UserPasswordReset({
    item,
    policy,
    resetPassword,
    isPasswordVisible,
    setResetPasswords,
    onToggleVisibility,
    onReset,
}) {
    return (
        <>
            <div className="user-password-reset">
                <div className="password-action-field compact">
                    <input
                        type={isPasswordVisible ? "text" : "password"}
                        placeholder="New password"
                        value={resetPassword}
                        disabled={!policy.canResetPassword}
                        autoComplete="new-password"
                        minLength={8}
                        aria-label={`New password for ${item.email}`}
                        onChange={(event) => setResetPasswords((current) => ({
                            ...current,
                            [item.id]: event.target.value,
                        }))}
                    />

                    <button
                        type="button"
                        className="user-password-icon-button"
                        disabled={!policy.canResetPassword}
                        onClick={() => onToggleVisibility(item.id)}
                        aria-label={
                            isPasswordVisible
                                ? `Hide reset password for ${item.email}`
                                : `Show reset password for ${item.email}`
                        }
                        aria-pressed={isPasswordVisible}
                    >
                        <img
                            src={isPasswordVisible ? "/hide.png" : "/eye.png"}
                            alt=""
                            aria-hidden="true"
                        />
                    </button>
                </div>

                <button
                    type="button"
                    className="user-table-action-button user-reset-button"
                    disabled={!policy.canResetPassword || resetPassword.length < 8}
                    onClick={() => onReset(item)}
                >
                    Change
                </button>
            </div>

            {policy.resetReason && (
                <small className="user-policy-note">{policy.resetReason}</small>
            )}
        </>
    );
}
