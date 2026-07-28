/**
 * @file UserRow.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import { getUserAdminPolicy } from "../../utils/userAdminPolicy";
import { formatRoleLabel } from "../../utils/userFormatters";
import { getUserInitials } from "../../utils/users/userInitials";
import UserPasswordReset from "./UserPasswordReset";
import UserStatusBadge from "./UserStatusBadge";

export default function UserRow({
    item,
    users,
    currentUser,
    resetPasswords,
    setResetPasswords,
    visibleResetPasswords,
    onToggleResetPasswordVisibility,
    onReset,
    onToggle,
}) {
    const policy = getUserAdminPolicy({ targetUser: item, currentUser, users });
    const isPasswordVisible = Boolean(visibleResetPasswords[item.id]);
    const resetPassword = resetPasswords[item.id] || "";

    return (
        <tr className={!item.is_active ? "user-row-inactive" : ""}>
            <td className="user-identity-cell" data-label="Name">
                <div className="user-identity">
                    <span className="user-avatar" aria-hidden="true">
                        {getUserInitials(item.full_name)}
                    </span>
                    <div className="user-identity-copy">
                        <strong>{item.full_name || "Unnamed user"}</strong>
                        {String(item.id) === String(currentUser?.id) && (
                            <span className="current-user-label">Your account</span>
                        )}
                    </div>
                </div>
            </td>

            <td className="user-email-cell" data-label="Email">
                <span>{item.email}</span>
            </td>

            <td className="user-role-cell" data-label="Role">
                <span className="user-role-badge">{formatRoleLabel(item.role)}</span>
            </td>

            <td className="user-status-cell" data-label="Status">
                <UserStatusBadge active={item.is_active} />
            </td>

            <td className="user-password-cell" data-label="Password Reset">
                <UserPasswordReset
                    item={item}
                    policy={policy}
                    resetPassword={resetPassword}
                    isPasswordVisible={isPasswordVisible}
                    setResetPasswords={setResetPasswords}
                    onToggleVisibility={onToggleResetPasswordVisibility}
                    onReset={onReset}
                />
            </td>

            <td className="user-actions-cell" data-label="Actions">
                <div className="user-row-actions">
                    <button
                        type="button"
                        className={
                            item.is_active
                                ? "user-table-action-button user-disable-button"
                                : "user-table-action-button user-enable-button"
                        }
                        disabled={!policy.canToggleActive}
                        onClick={() => onToggle(item)}
                    >
                        {item.is_active ? "Disable" : "Enable"}
                    </button>
                </div>

                {policy.toggleReason && (
                    <small className="user-policy-note">{policy.toggleReason}</small>
                )}
            </td>
        </tr>
    );
}
