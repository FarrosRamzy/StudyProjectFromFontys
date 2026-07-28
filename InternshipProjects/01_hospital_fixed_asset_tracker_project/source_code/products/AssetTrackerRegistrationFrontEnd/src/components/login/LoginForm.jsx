/**
 * @file LoginForm.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


export default function LoginForm({
    email,
    setEmail,
    password,
    setPassword,
    showPassword,
    setShowPassword,
    submitting,
    error,
    notice,
    onSubmit,
}) {
    return (
        <section className="login-card-wrap">
            <form className="login-card" onSubmit={onSubmit}>
                <div>
                    <p className="eyebrow">Authorized Staff Only</p>
                    <h2>Sign in</h2>
                    <p className="login-subtitle">Use your hospital staff account to continue.</p>
                </div>

                {notice && <div className="auth-notice">{notice}</div>}
                {error && <div className="auth-error">{error}</div>}

                <label>
                    Email
                    <input type="email" value={email} onChange={(event) => setEmail(event.target.value)} placeholder="Enter your email" autoComplete="username" required />
                </label>

                <label>
                    Password
                    <div className="password-field password-input-with-icon">
                        <input type={showPassword ? "text" : "password"} value={password} onChange={(event) => setPassword(event.target.value)} placeholder="Enter your password" autoComplete="current-password" required />
                        <button type="button" className="password-icon-button" onClick={() => setShowPassword((current) => !current)} aria-label={showPassword ? "Hide password" : "Show password"}>
                            <img src={showPassword ? "/hide.png" : "/eye.png"} alt="" aria-hidden="true" />
                        </button>
                    </div>
                </label>

                <button type="submit" className="login-submit" disabled={submitting}>
                    {submitting ? "Signing in..." : "Sign In"}
                </button>
                <p className="security-note">Access is restricted to authorized hospital personnel.</p>
            </form>
        </section>
    );
}
