/**
 * @file node_clock.h
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-14
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <Arduino.h>
#include "interfaces/i_node_clock.h"

class NodeClock : public INodeClock
{
public:
    NodeClock();
    ~NodeClock();

    uint32_t millisNow() const override;
};