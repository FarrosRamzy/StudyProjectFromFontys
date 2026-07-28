/**
 * @file DashboardActionCard.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


export default function DashboardActionCard({ title, message, onClick }) {
    return (
        <button type="button" className="dashboard-action-card" onClick={onClick}>
            <strong>{title}</strong>
            <p>{message}</p>
        </button>
    );
}
