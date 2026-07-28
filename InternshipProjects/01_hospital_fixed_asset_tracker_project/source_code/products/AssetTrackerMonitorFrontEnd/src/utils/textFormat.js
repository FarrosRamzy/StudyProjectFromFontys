/**
 * @file textFormat.js
 * @author Farros Ramzy (you@domain.com)
 * @description Text formatting helpers for monitor UI.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


export function normalizeText(value) {
    return String(value ?? "").trim();
}

export function normalizeSearchText(value) {
    return normalizeText(value).toLowerCase();
}

export function isBlank(value) {
    return normalizeText(value).length === 0;
}

export function formatFallback(value, fallback = "-") {
    const text = normalizeText(value);
    return text || fallback;
}

export function toTitleCase(value) {
    const text = normalizeText(value);

    if (!text) {
        return "";
    }

    return text
        .replace(/[_-]+/g, " ")
        .toLowerCase()
        .split(" ")
        .filter(Boolean)
        .map((word) => word.charAt(0).toUpperCase() + word.slice(1))
        .join(" ");
}

export function formatStatusLabel(value) {
    return toTitleCase(value);
}

export function formatRoleLabel(value) {
    return toTitleCase(value);
}

export function shortenMiddle(value, maxLength = 24) {
    const text = normalizeText(value);

    if (text.length <= maxLength) {
        return text;
    }

    const visibleLength = Math.max(maxLength - 3, 4);
    const startLength = Math.ceil(visibleLength / 2);
    const endLength = Math.floor(visibleLength / 2);

    return `${text.slice(0, startLength)}...${text.slice(-endLength)}`;
}

export function formatTagId(tagId) {
    return shortenMiddle(tagId, 28);
}

export function formatDeviceId(deviceId) {
    return shortenMiddle(deviceId, 24);
}

export function buildSearchText(values = []) {
    return values
        .filter((value) => value !== null && value !== undefined)
        .map((value) => String(value).toLowerCase())
        .join(" ");
}

export function includesSearchKeyword(values = [], keyword = "") {
    const search = normalizeSearchText(keyword);

    if (!search) {
        return true;
    }

    return buildSearchText(values).includes(search);
}

export function pluralize(count, singular, plural = `${singular}s`) {
    return Number(count) === 1 ? singular : plural;
}

export function formatCountLabel(count, singular, plural = `${singular}s`) {
    return `${count} ${pluralize(count, singular, plural)}`;
}
