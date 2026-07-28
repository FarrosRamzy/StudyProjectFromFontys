/**
 * @file UserManagement.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Admin-only page for creating and managing user accounts.
 * @version 1.0.0
 * @date 2026-06-04

 * @Copyright (c) 2026
 */


import RegistrationModuleNav from "../components/common/RegistrationModuleNav";
import RegistrationTopbar from "../components/common/RegistrationTopbar";
import MessageBanner from "../components/common/MessageBanner";
import UserCreateForm from "../components/users/UserCreateForm";
import UserTable from "../components/users/UserTable";
import { useAuth } from "../context/AuthContext";
import { useAuthActions } from "../hooks/useAuthAction";
import { useUserManagement } from "../hooks/users/useUserManagement";

export default function UserManagement() {
    const { user } = useAuth();
    const { handleLogout } = useAuthActions();

    const {
        users,
        form,
        setForm,
        resetPasswords,
        setResetPasswords,
        visibleResetPasswords,
        showCreatePassword,
        setShowCreatePassword,
        loading,
        saving,
        error,
        successMessage,
        refreshUsers,
        updateForm,
        handleCreateUser,
        handleResetPassword,
        handleToggleActive,
        toggleResetPasswordVisibility,
    } = useUserManagement();

    return (
        <main className="app-shell user-admin-page">
            <div className="sticky-page-header">
                <RegistrationTopbar
                    user={user}
                    subtitle="User Administration"
                    onRefresh={refreshUsers}
                    onLogout={handleLogout}
                />
                <RegistrationModuleNav role={user?.role} />
            </div>

            <section className="page-hero">
                <div className="hero-main">
                    <p className="eyebrow">Admin Console</p>
                    <h1>User Accounts</h1>
                    <p className="hero-copy">
                        Create staff accounts, assign roles, and reset passwords.
                    </p>
                </div>
            </section>

            <MessageBanner error={error} successMessage={successMessage} />

            <section className="panel user-form-panel">
                <div className="section-header">
                    <div>
                        <h2>Create User</h2>
                        <p>Add an account for registration, monitoring, technician, or admin access.</p>
                    </div>
                </div>
                <UserCreateForm
                    form={form}
                    setForm={setForm}
                    updateForm={updateForm}
                    saving={saving}
                    showCreatePassword={showCreatePassword}
                    setShowCreatePassword={setShowCreatePassword}
                    onSubmit={handleCreateUser}
                />
            </section>

            <section className="table-panel user-table-panel">
                <div className="section-header">
                    <div>
                        <h2>Existing Users</h2>
                        <p>{users.length} accounts registered</p>
                    </div>
                </div>
                {loading ? (
                    <p className="user-muted">Loading users...</p>
                ) : (
                    <UserTable
                        users={users}
                        currentUser={user}
                        resetPasswords={resetPasswords}
                        setResetPasswords={setResetPasswords}
                        visibleResetPasswords={visibleResetPasswords}
                        onToggleResetPasswordVisibility={toggleResetPasswordVisibility}
                        onReset={handleResetPassword}
                        onToggle={handleToggleActive}
                    />
                )}
            </section>
        </main>
    );
}
