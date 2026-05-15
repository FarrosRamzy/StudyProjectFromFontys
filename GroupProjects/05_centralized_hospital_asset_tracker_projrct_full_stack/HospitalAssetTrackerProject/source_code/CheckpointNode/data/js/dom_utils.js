/**
 * @file dom_utils.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-13

 * @Copyright (c) 2026
 */

/**
 * @file dom_utils.js
 * @description DOM helper functions.
 */

export function byId(id) {
    return document.getElementById(id);
}

export function getQueryParam(name) {
    const params = new URLSearchParams(window.location.search);
    return params.get(name);
}