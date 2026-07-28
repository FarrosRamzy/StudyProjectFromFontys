/**
 * @file Login.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Login page for the Hospital Asset Monitor app.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { LoginBrand } from "../components/auth/LoginBrand";
import { LoginLoadingPanel } from "../components/auth/LoginLoadingPanel";
import { PasswordField } from "../components/auth/PasswordField";
import { useLoginForm } from "../hooks/auth/useLoginForm";

export function Login({ error = "", notice = "", onLogin }) {
    const form = useLoginForm({ error, notice, onLogin });

    return (
        <main className="auth-page">
            <section className="auth-card">
                <LoginBrand />
                {form.noticeMessage && <div className="message-banner success">{form.noticeMessage}</div>}
                {form.errorMessage && <div className="message-banner error">{form.errorMessage}</div>}
                <form className="form-stack" onSubmit={form.submit}>
                    <label className="field">
                        <span>Email</span>
                        <input
                            type="email"
                            value={form.email}
                            onChange={(event) => {
                                form.setEmail(event.target.value);
                                form.clearMessages();
                            }}
                            placeholder="Enter email"
                            autoComplete="email"
                        />
                    </label>
                    <PasswordField
                        password={form.password}
                        setPassword={form.setPassword}
                        showPassword={form.showPassword}
                        setShowPassword={form.setShowPassword}
                        onClear={form.clearMessages}
                    />
                    <SubmitButton submitting={form.submitting} />
                    {form.submitting && <LoginLoadingPanel slowLoading={form.slowLoading} />}
                </form>
            </section>
        </main>
    );
}

function SubmitButton({ submitting }) {
    return (
        <button type="submit" className="primary-button auth-submit-button" disabled={submitting}>
            {submitting ? (
                <span className="button-loading-content">
                    <span className="button-spinner" aria-hidden="true" />
                    Signing in...
                </span>
            ) : "Sign In"}
        </button>
    );
}
