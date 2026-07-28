/**
 * @file PasswordVisibilityButton.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


export default function PasswordVisibilityButton({ visible, onClick, labelPrefix }) {
    return (
        <button
            type="button"
            className="password-icon-button"
            onClick={onClick}
            aria-label={visible ? `Hide ${labelPrefix}` : `Show ${labelPrefix}`}
        >
            <img src={visible ? "/hide.png" : "/eye.png"} alt="" aria-hidden="true" />
        </button>
    );
}
