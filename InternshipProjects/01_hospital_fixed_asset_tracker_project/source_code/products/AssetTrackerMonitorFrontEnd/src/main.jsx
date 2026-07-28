/**
 * @file main.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description React entry point for the Hospital Asset Monitor app.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import React from "react";
import ReactDOM from "react-dom/client";
import App from "./App.jsx";

import "./index.css";
import "./styles/base.css";
import "./styles/components.css";
import "./styles/pages.css";

ReactDOM.createRoot(document.getElementById("root")).render(
    <React.StrictMode>
        <App />
    </React.StrictMode>
);
