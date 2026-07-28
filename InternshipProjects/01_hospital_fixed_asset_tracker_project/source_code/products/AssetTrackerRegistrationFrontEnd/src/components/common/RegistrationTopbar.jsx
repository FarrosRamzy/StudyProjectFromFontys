/**
 * @file RegistrationTopbar.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-15

 * @Copyright (c) 2026
 */


import { formatRoleLabel, getDisplayName } from "../../utils/userFormatters";

export default function RegistrationTopbar({
    user,
    subtitle = "Registration Console",
    onRefresh,
    onLogout,
}) {
    return (
        <header className="app-topbar">
            <div className="app-brand-lockup">
                <span className="app-brand-mark">
                    <img
                        src="/stethoscope.png"
                        alt=""
                        aria-hidden="true"
                    />
                </span>

                <div>
                    <strong>Hospital Asset Tracker</strong>
                    <span>{subtitle}</span>
                </div>
            </div>

            <div className="topbar-user">
                <div className="topbar-user-text">
                    <span>Signed in as</span>
                    <strong>{getDisplayName(user)}</strong>
                </div>

                <div className="topbar-user-actions">
                    <span className="topbar-role-badge">
                        {formatRoleLabel(user?.role)}
                    </span>

                    {onRefresh && (
                        <button
                            type="button"
                            className="topbar-refresh-button"
                            onClick={onRefresh}
                        >
                            Refresh
                        </button>
                    )}

                    <button
                        type="button"
                        className="topbar-logout-button"
                        onClick={onLogout}
                    >
                        Sign out
                    </button>
                </div>
            </div>
        </header>
    );
}