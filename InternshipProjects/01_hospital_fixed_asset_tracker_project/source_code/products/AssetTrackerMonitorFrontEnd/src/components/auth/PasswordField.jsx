/**
 * @file PasswordField.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


export function PasswordField({ password, setPassword, showPassword, setShowPassword, onClear }) {
    return (
        <label className="field">
            <span>Password</span>
            <div className="password-input-row password-input-with-icon">
                <input
                    type={showPassword ? "text" : "password"}
                    value={password}
                    onChange={(event) => {
                        setPassword(event.target.value);
                        onClear?.();
                    }}
                    placeholder="Enter password"
                    autoComplete="current-password"
                />
                <button
                    type="button"
                    className="password-icon-button"
                    onClick={() => setShowPassword((current) => !current)}
                    aria-label={showPassword ? "Hide password" : "Show password"}
                >
                    <img src={showPassword ? "/hide.png" : "/eye.png"} alt="" aria-hidden="true" />
                </button>
            </div>
        </label>
    );
}
