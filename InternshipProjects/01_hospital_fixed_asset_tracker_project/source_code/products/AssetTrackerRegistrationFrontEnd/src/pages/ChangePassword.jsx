/**
 * @file ChangePassword.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Password change page for all authenticated roles.
 * @version 1.0.0
 * @date 2026-06-04

 * @Copyright (c) 2026
 */


import ChangePasswordForm from "../components/account/ChangePasswordForm";
import MessageBanner from "../components/common/MessageBanner";
import RegistrationModuleNav from "../components/common/RegistrationModuleNav";
import RegistrationTopbar from "../components/common/RegistrationTopbar";
import { useAuth } from "../context/AuthContext";
import { useChangePasswordForm } from "../hooks/account/useChangePasswordForm";
import { useAuthActions } from "../hooks/useAuthAction";

export default function ChangePassword() {
    const { user } = useAuth();
    const { handleLogout } = useAuthActions();
    const form = useChangePasswordForm();

    return (
        <main className="app-shell account-page">
            <div className="sticky-page-header">
                <RegistrationTopbar user={user} subtitle="Account Security" onLogout={handleLogout} />
                <RegistrationModuleNav role={user?.role} />
            </div>

            <section className="page-hero">
                <div className="hero-main">
                    <p className="eyebrow">Account Security</p>
                    <h1>Change Password</h1>
                    <p className="hero-copy">Update your own password using your current password.</p>
                </div>
            </section>

            <MessageBanner error={form.error} successMessage={form.successMessage} />

            <section className="panel account-panel narrow-panel">
                <div className="section-header">
                    <div>
                        <h2>Password Update</h2>
                        <p>Use at least 8 characters. You will stay signed in after changing it.</p>
                    </div>
                </div>
                <ChangePasswordForm form={form} />
            </section>
        </main>
    );
}
