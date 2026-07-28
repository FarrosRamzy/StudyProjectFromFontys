/**
 * @file my_node_duplicate_tag_filter.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-06-25
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "my_node_core_lib/my_node_duplicate_tag_filter.h"

#include <string.h>

void resetDuplicateTagState(MyNodeDuplicateTagState *state)
{
    if (state == nullptr)
    {
        return;
    }

    state->last_tag_id[0] = '\0';
    state->last_seen_ms = 0;
}

bool isDuplicateTagCore(
    MyNodeDuplicateTagState *state,
    const char *tag_id,
    uint32_t now_ms,
    uint32_t suppress_ms)
{
    if (state == nullptr || tag_id == nullptr || tag_id[0] == '\0')
    {
        return false;
    }

    bool same_tag = strcmp(state->last_tag_id, tag_id) == 0;
    bool inside_window = (uint32_t)(now_ms - state->last_seen_ms) < suppress_ms;

    if (same_tag && inside_window)
    {
        return true;
    }

    strncpy(state->last_tag_id, tag_id, sizeof(state->last_tag_id) - 1);
    state->last_tag_id[sizeof(state->last_tag_id) - 1] = '\0';
    state->last_seen_ms = now_ms;

    return false;
}
