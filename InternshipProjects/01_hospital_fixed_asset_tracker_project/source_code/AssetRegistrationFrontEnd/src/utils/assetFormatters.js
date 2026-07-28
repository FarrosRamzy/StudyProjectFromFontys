/**
 * @file assetFormatters.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-08

 * @Copyright (c) 2026
 */

export function formatTagId(tagId) {
  if (!tagId) {
    return "-";
  }

  if (tagId.length <= 18) {
    return tagId;
  }

  return `${tagId.slice(0, 4)}-${tagId.slice(-4)}`;
}

export function formatDateTime(value) {
  if (!value) {
    return "-";
  }

  const date = new Date(value);

  if (Number.isNaN(date.getTime())) {
    return value;
  }

  return date.toLocaleString();
}