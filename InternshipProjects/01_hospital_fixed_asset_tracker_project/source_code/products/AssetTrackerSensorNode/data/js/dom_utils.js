/**
 * @file dom_utils.js
 * @author Farros Ramzy (you@domain.com)
 * @description DOM helper functions.
 * @version 1.0.0
 * @date 2026-05-13

 * @Copyright (c) 2026
 */

export function byId(id) {
    return document.getElementById(id);
}

export function getQueryParam(name) {
    const params = new URLSearchParams(window.location.search);
    return params.get(name);
}
