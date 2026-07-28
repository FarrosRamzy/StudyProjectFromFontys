/**
 * @file SearchInput.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Reusable search input component.
 * @version 1.0.0
 * @date 2026-05-22

 * @Copyright (c) 2026
 */


export function SearchInput({
    value,
    onChange,
    placeholder = "Search...",
    className = "",
    autoFocus = false,
}) {
    return (
        <input
            type="search"
            className={`monitor-search ${className}`.trim()}
            value={value}
            onChange={(event) => onChange?.(event.target.value)}
            placeholder={placeholder}
            autoFocus={autoFocus}
        />
    );
}
