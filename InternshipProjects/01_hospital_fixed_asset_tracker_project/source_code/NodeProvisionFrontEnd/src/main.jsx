/**
 * @file main.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description React entry point for the Node Registration App.
 * @version 1.0.0
 * @date 2026-04-21

 * @Copyright (c) 2026
 */

import React from "react";
import ReactDOM from "react-dom/client";
import { BrowserRouter } from "react-router-dom";
import App from "./App.jsx";
import { AuthProvider } from "./context/AuthContext.jsx";
import "./index.css";

ReactDOM.createRoot(document.getElementById("root")).render(
    <React.StrictMode>
        <BrowserRouter>
            <AuthProvider>
                <App />
            </AuthProvider>
        </BrowserRouter>
    </React.StrictMode>
);
