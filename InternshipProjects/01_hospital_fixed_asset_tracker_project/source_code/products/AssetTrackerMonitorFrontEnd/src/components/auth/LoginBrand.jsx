/**
 * @file LoginBrand.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


export function LoginBrand() {
    return (
        <>
            <div className="auth-brand">
                <span className="app-brand-mark"><img src="/stethoscope.png" alt="" aria-hidden="true" /></span>
                <div><strong>Hospital Asset Tracker</strong><span>Asset Monitor Console</span></div>
            </div>
            <div className="auth-heading">
                <h1>Sign in</h1>
                <p>Sign in to monitor asset locations, node health, movement requests, and tracking warnings.</p>
            </div>
        </>
    );
}
