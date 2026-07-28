#pragma once

#include <stdint.h>

bool isIntervalDue(
    uint32_t now_ms,
    uint32_t last_ms,
    uint32_t interval_ms);
