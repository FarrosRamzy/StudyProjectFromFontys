/**
 * @file ChangePasswordForm.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import PasswordVisibilityButton from "./PasswordVisibilityButton";

export default function ChangePasswordForm({ form }) {
    return (
        <form className="account-form password-update-form" onSubmit={form.handleSubmit}>
            <div className="password-section">
                <div className="password-section-header">
                    <div>
                        <h3>Verify current password</h3>
                        <p>Enter your existing password before setting a new one.</p>
                    </div>
                </div>
                <label>
                    Current password
                    <input type="password" value={form.currentPassword} onChange={(e) => form.setCurrentPassword(e.target.value)} required />
                </label>
            </div>

            <div className="password-section new-password-section">
                <div className="password-section-header">
                    <div>
                        <h3>Create new password</h3>
                        <p>Use at least 8 characters. Avoid reusing old passwords.</p>
                    </div>
                </div>

                <PasswordField
                    label="New password"
                    value={form.newPassword}
                    onChange={form.setNewPassword}
                    visible={form.showNewPasswords}
                    setVisible={form.setShowNewPasswords}
                    labelPrefix="new password"
                />
                <PasswordField
                    label="Confirm new password"
                    value={form.confirmPassword}
                    onChange={form.setConfirmPassword}
                    visible={form.showNewPasswords}
                    setVisible={form.setShowNewPasswords}
                    labelPrefix="confirmed password"
                />

                <div className="password-helper-card">
                    <strong>Password tips</strong>
                    <span>Use a mix of letters, numbers, and symbols. Do not share passwords between staff accounts.</span>
                </div>
            </div>

            <div className="account-form-actions">
                <button type="submit" className="primary-button" disabled={form.saving}>
                    {form.saving ? "Saving..." : "Update Password"}
                </button>
            </div>
        </form>
    );
}

function PasswordField({ label, value, onChange, visible, setVisible, labelPrefix }) {
    return (
        <label>
            {label}
            <div className="account-password-field">
                <input
                    type={visible ? "text" : "password"}
                    value={value}
                    onChange={(event) => onChange(event.target.value)}
                    minLength={8}
                    required
                />
                <PasswordVisibilityButton
                    visible={visible}
                    onClick={() => setVisible((current) => !current)}
                    labelPrefix={labelPrefix}
                />
            </div>
        </label>
    );
}
