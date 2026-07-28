/**
 * @file AccessItem.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


export default function AccessItem({ title, message, tone = "" }) {
    return (
        <article className={`access-summary-card ${tone}`}>
            <div className="access-summary-title">
                <strong>{title}</strong>
            </div>
            <p>{message}</p>
        </article>
    );
}
