/**
 * @file DashboardStatCard.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


export function DashboardStatCard({ label, value, detail, tone = "neutral", onClick }) {
    return (
        <button type="button" className={`monitor-stat-card ${tone}`} onClick={onClick}>
            <span>{label}</span>
            <strong>{value}</strong>
            <p>{detail}</p>
        </button>
    );
}
