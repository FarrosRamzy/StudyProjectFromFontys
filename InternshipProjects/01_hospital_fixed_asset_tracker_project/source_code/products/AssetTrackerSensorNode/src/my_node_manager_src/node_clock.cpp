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

/**
 * @brief Construct a new Node Clock:: Node Clock object
 * 
 */
NodeClock::NodeClock()
{
}

/**
 * @brief Destroy the Node Clock:: Node Clock object
 * 
 */
NodeClock::~NodeClock()
{
}

/**
 * @brief 
 * 
 * @return uint32_t 
 */
uint32_t NodeClock::millisNow() const
{
    return millis();
}
