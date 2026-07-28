/**
 * @file UserTable.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import UserRow from "./UserRow";

export default function UserTable({
    users,
    currentUser,
    resetPasswords,
    setResetPasswords,
    visibleResetPasswords,
    onToggleResetPasswordVisibility,
    onReset,
    onToggle,
}) {
    if (users.length === 0) {
        return (
            <div className="user-table-empty">
                <strong>No user accounts found</strong>
                <span>Create the first staff account using the form above.</span>
            </div>
        );
    }

    return (
        <div className="user-table-wrap">
            <table className="user-table">
                <colgroup>
                    <col className="user-name-column" />
                    <col className="user-email-column" />
                    <col className="user-role-column" />
                    <col className="user-status-column" />
                    <col className="user-password-column" />
                    <col className="user-actions-column" />
                </colgroup>
                <thead>
                    <tr>
                        <th scope="col">Name</th>
                        <th scope="col">Email</th>
                        <th scope="col">Role</th>
                        <th scope="col">Status</th>
                        <th scope="col">Password Reset</th>
                        <th scope="col">Actions</th>
                    </tr>
                </thead>
                <tbody>
                    {users.map((item) => (
                        <UserRow
                            key={item.id}
                            item={item}
                            users={users}
                            currentUser={currentUser}
                            resetPasswords={resetPasswords}
                            setResetPasswords={setResetPasswords}
                            visibleResetPasswords={visibleResetPasswords}
                            onToggleResetPasswordVisibility={onToggleResetPasswordVisibility}
                            onReset={onReset}
                            onToggle={onToggle}
                        />
                    ))}
                </tbody>
            </table>
        </div>
    );
}
