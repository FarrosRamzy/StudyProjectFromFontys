/**
 * @file RegistrationModuleNav.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-15

 * @Copyright (c) 2026
 */


import { NavLink } from "react-router-dom";

import {
    canAccessAssetRegistration,
    canAccessDashboard,
    canAccessNodeRegistration,
    canAccessSystemSettings,
    canAccessUserManagement,
} from "../../utils/userFormatters";

export default function RegistrationModuleNav({ role }) {
    return (
        <nav className="module-nav">
            {canAccessDashboard(role) && (
                <NavLink to="/dashboard">Dashboard</NavLink>
            )}

            {canAccessNodeRegistration(role) && (
                <NavLink to="/nodes">Node Registration</NavLink>
            )}

            {canAccessAssetRegistration(role) && (
                <NavLink to="/assets">Asset Registration</NavLink>
            )}

            {canAccessUserManagement(role) && (
                <NavLink to="/users">User Accounts</NavLink>
            )}

            <NavLink to="/account/password">Change Password</NavLink>

            {canAccessSystemSettings(role) && (
                <NavLink to="/settings">System Settings</NavLink>
            )}
        </nav>
    );
}
