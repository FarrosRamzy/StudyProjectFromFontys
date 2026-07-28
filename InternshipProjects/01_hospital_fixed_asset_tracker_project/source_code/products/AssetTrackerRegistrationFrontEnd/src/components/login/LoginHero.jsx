/**
 * @file LoginHero.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


export default function LoginHero() {
    return (
        <section className="login-hero">
            <div className="login-brand">
                <span className="brand-badge">Hospital Asset Tracker</span>
                <h1>Secure access for hospital asset operations.</h1>
                <p>
                    Register RFID nodes & Hospital Assets, manage checkpoint devices,
                    and protect hospital asset visibility through authorized staff access.
                </p>
                <div className="login-trust-list">
                    <span>RFID Asset Tracking</span>
                    <span>Node Registration</span>
                    <span>Asset Registration</span>
                    <span>Account Management</span>
                </div>
            </div>
        </section>
    );
}
