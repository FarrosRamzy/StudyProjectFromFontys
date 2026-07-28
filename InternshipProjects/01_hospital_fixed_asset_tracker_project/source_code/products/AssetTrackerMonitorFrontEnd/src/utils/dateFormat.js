/**
 * @file dateFormat.js
 * @author Farros Ramzy (you@domain.com)
 * @description Date/time formatting helpers for monitor UI.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


export function isValidDate(value) {
    if (!value) {
        return false;
    }

    const date = new Date(value);
    return !Number.isNaN(date.getTime());
}

export function formatDateTime(value) {
    if (!isValidDate(value)) {
        return "-";
    }

    return new Date(value).toLocaleString("en-GB", {
        year: "numeric",
        month: "short",
        day: "2-digit",
        hour: "2-digit",
        minute: "2-digit",
        second: "2-digit",
    });
}

export function formatDate(value) {
    if (!isValidDate(value)) {
        return "-";
    }

    return new Date(value).toLocaleDateString("en-GB", {
        year: "numeric",
        month: "short",
        day: "2-digit",
    });
}

export function formatTime(value) {
    if (!isValidDate(value)) {
        return "-";
    }

    return new Date(value).toLocaleTimeString("en-GB", {
        hour: "2-digit",
        minute: "2-digit",
        second: "2-digit",
    });
}

export function getRelativeTime(value) {
    if (!isValidDate(value)) {
        return "-";
    }

    const date = new Date(value);
    const now = new Date();

    const diffMs = now.getTime() - date.getTime();
    const diffSeconds = Math.floor(diffMs / 1000);
    const diffMinutes = Math.floor(diffSeconds / 60);
    const diffHours = Math.floor(diffMinutes / 60);
    const diffDays = Math.floor(diffHours / 24);

    if (diffSeconds < 10) {
        return "just now";
    }

    if (diffSeconds < 60) {
        return `${diffSeconds} sec ago`;
    }

    if (diffMinutes < 60) {
        return `${diffMinutes} min ago`;
    }

    if (diffHours < 24) {
        return `${diffHours} hr ago`;
    }

    if (diffDays < 7) {
        return `${diffDays} day${diffDays > 1 ? "s" : ""} ago`;
    }

    return formatDateTime(value);
}

export function getAgeInSeconds(value) {
    if (!isValidDate(value)) {
        return null;
    }

    const date = new Date(value);
    const now = new Date();

    return Math.floor((now.getTime() - date.getTime()) / 1000);
}

export function isOlderThanSeconds(value, seconds) {
    const age = getAgeInSeconds(value);

    if (age === null) {
        return false;
    }

    return age > seconds;
}
