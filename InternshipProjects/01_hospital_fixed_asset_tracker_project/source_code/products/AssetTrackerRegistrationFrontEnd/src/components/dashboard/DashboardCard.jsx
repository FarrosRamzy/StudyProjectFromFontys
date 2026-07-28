/**
 * @file DashboardCard.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


export default function DashboardCard({ label, value, detail, tone = "neutral", onClick }) {
    return (
        <button
            type="button"
            className={`registration-dashboard-card ${tone}`}
            onClick={onClick}
        >
            <span>{label}</span>
            <strong>{value}</strong>
            <p>{detail}</p>
        </button>
    );
}
