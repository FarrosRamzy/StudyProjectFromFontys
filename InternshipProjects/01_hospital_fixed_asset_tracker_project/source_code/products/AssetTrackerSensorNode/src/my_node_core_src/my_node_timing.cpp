/**
 * @file my_node_timing.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-06-25
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "my_node_core_lib/my_node_timing.h"

bool isIntervalDue(
    uint32_t now_ms,
    uint32_t last_ms,
    uint32_t interval_ms)
{
    return (uint32_t)(now_ms - last_ms) >= interval_ms;
}
