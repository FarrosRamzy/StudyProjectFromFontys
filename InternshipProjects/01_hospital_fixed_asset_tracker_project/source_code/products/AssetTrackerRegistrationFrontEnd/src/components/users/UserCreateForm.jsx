/**
 * @file UserCreateForm.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import { USER_ROLES } from "../../services/userApi";

export default function UserCreateForm({
    form,
    setForm,
    updateForm,
    saving,
    showCreatePassword,
    setShowCreatePassword,
    onSubmit,
}) {
    return (
        <form className="user-form-grid" onSubmit={onSubmit}>
            <label>
                Full name
                <input
                    value={form.full_name}
                    onChange={(event) => updateForm("full_name", event.target.value)}
                    required
                />
            </label>

            <label>
                Email
                <input
                    type="email"
                    value={form.email}
                    onChange={(event) => updateForm("email", event.target.value)}
                    required
                />
            </label>

            <label>
                Password
                <div className="password-action-field">
                    <input
                        type={showCreatePassword ? "text" : "password"}
                        value={form.password}
                        onChange={(event) => setForm((current) => ({
                            ...current,
                            password: event.target.value,
                        }))}
                        placeholder="Enter password"
                        autoComplete="new-password"
                        minLength={8}
                        required
                    />

                    <button
                        type="button"
                        className="user-password-icon-button"
                        onClick={() => setShowCreatePassword((current) => !current)}
                        aria-label={showCreatePassword ? "Hide password" : "Show password"}
                    >
                        <img
                            src={showCreatePassword ? "/hide.png" : "/eye.png"}
                            alt=""
                            aria-hidden="true"
                        />
                    </button>
                </div>
            </label>

            <label>
                Role
                <select
                    value={form.role}
                    onChange={(event) => updateForm("role", event.target.value)}
                >
                    {USER_ROLES.map((role) => (
                        <option key={role.value} value={role.value}>
                            {role.label}
                        </option>
                    ))}
                </select>
            </label>

            <button className="primary-button" disabled={saving}>
                {saving ? "Creating..." : "Create User"}
            </button>
        </form>
    );
}
