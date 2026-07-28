/**
 * @file App.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-04

 * @Copyright (c) 2026
 */


import { Navigate, Routes, Route } from "react-router-dom";
import SetupAwareLogin from "./routes/SetupAwareLogin";
import SetupAdminPage from "./pages/SetupAdminPage";
import NodeRegistration from "./pages/NodeRegistration";
import AssetRegistration from "./pages/AssetRegistration";
import UserManagement from "./pages/UserManagement";
import ChangePassword from "./pages/ChangePassword";
import SystemSettings from "./pages/SystemSettings";
import ProtectedRoute from "./routes/ProtectedRoute";
import RegistrationDashboard from "./pages/RegistrationDashboard";
import "./App.css";

const ALL_ROLES = [
  "admin",
  "test_user",
  "technician",
  "registration_staff",
  "monitor_staff",
];

function HomeRedirect() {
  return <Navigate to="/dashboard" replace />;
}

function App() {
  return (
    <Routes>
      <Route path="/login" element={<SetupAwareLogin />} />
      <Route path="/setup-admin" element={<SetupAdminPage />} />

      <Route
        path="/"
        element={
          <ProtectedRoute allowedRoles={ALL_ROLES}>
            <HomeRedirect />
          </ProtectedRoute>
        }
      />

      <Route
        path="/dashboard"
        element={
          <ProtectedRoute allowedRoles={ALL_ROLES}>
            <RegistrationDashboard />
          </ProtectedRoute>
        }
      />

      <Route
        path="/nodes"
        element={
          <ProtectedRoute allowedRoles={["admin", "test_user", "technician"]}>
            <NodeRegistration />
          </ProtectedRoute>
        }
      />

      <Route
        path="/assets"
        element={
          <ProtectedRoute
            allowedRoles={["admin", "test_user", "registration_staff"]}
          >
            <AssetRegistration />
          </ProtectedRoute>
        }
      />

      <Route
        path="/users"
        element={
          <ProtectedRoute allowedRoles={["admin"]}>
            <UserManagement />
          </ProtectedRoute>
        }
      />

      <Route
        path="/settings"
        element={
          <ProtectedRoute allowedRoles={["admin", "test_user"]}>
            <SystemSettings />
          </ProtectedRoute>
        }
      />

      <Route
        path="/account/password"
        element={
          <ProtectedRoute allowedRoles={ALL_ROLES}>
            <ChangePassword />
          </ProtectedRoute>
        }
      />

      <Route path="*" element={<Navigate to="/" replace />} />
    </Routes>
  );
}

export default App;
