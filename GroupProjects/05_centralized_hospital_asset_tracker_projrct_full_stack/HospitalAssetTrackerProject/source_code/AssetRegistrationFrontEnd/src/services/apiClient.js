/**
 * @file apiClient.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-08

 * @Copyright (c) 2026
 */

const API_BASE = import.meta.env.VITE_API_BASE_URL ?? "http://localhost:8010";

export async function requestJson(path, options = {}) {
    const url = `${API_BASE}${path}`;

    const response = await fetch(url, options);

    let data = null;

    try {
        data = await response.json();
    } catch {
        data = null;
    }

    if (!response.ok) {
        throw new Error(data?.message || `Request failed: ${response.status}`);
    }

    return data;
}