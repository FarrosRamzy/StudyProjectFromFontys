#pragma once

#include <stdint.h>
#include <stddef.h>

struct MyNodeDuplicateTagState
{
    char last_tag_id[65];
    uint32_t last_seen_ms;
};

void resetDuplicateTagState(MyNodeDuplicateTagState *state);

bool isDuplicateTagCore(
    MyNodeDuplicateTagState *state,
    const char *tag_id,
    uint32_t now_ms,
    uint32_t suppress_ms);
