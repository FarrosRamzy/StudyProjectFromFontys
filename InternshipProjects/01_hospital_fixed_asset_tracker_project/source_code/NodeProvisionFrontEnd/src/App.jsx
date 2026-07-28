/**
 * @file App.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-04-21

 * @Copyright (c) 2026
 */

import NodeRegistration from "./pages/NodeRegistration"
import { Routes, Route } from "react-router-dom";
import LoginPage from "./pages/LoginPage";
import ProtectedRoute from "./routes/ProtectedRoute";
import './App.css'

function App() {
  return (
    <Routes>
      <Route path="/login" element={<LoginPage />} />

      <Route
        path="/"
        element={
          <ProtectedRoute allowedRoles={["admin", "technician"]}>
            <NodeRegistration />
          </ProtectedRoute>
        }
      />
    </Routes>
  );
}

export default App