/**
 * @file i_node_clock.h
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-14
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <stdint.h>

class INodeClock
{
public:
   ~INodeClock() {}

   virtual uint32_t millisNow() const = 0;
};
