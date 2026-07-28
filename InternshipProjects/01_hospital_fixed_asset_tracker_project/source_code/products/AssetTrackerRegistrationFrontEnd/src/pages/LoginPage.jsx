/**
 * @file LoginPage.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-18

 * @Copyright (c) 2026
 */


import { Navigate, useLocation, useNavigate } from "react-router-dom";
import LoginForm from "../components/login/LoginForm";
import LoginHero from "../components/login/LoginHero";
import { useAuth } from "../context/AuthContext";
import { useLoginForm } from "../hooks/login/useLoginForm";

export default function LoginPage() {
    const navigate = useNavigate();
    const location = useLocation();
    const { login, isAuthenticated, authLoading } = useAuth();
    const loginForm = useLoginForm({ location, navigate, login });

    if (!authLoading && isAuthenticated) {
        return <Navigate to="/" replace />;
    }

    return (
        <main className="login-page">
            <LoginHero />
            <LoginForm {...loginForm} onSubmit={loginForm.handleSubmit} />
        </main>
    );
}
