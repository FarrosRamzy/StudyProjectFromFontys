/**
 * @file node_clock.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-14
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_manager_lib/node_clock.h"

NodeClock::NodeClock()
{
}

NodeClock::~NodeClock()
{
}

uint32_t NodeClock::millisNow() const
{
    return millis();
}