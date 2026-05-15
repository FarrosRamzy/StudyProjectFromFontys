/**
 * @file node_board_control.h
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
#include <Esp.h>
#include "interfaces/i_node_board_control.h"

class NodeBoardControl : public INodeBoardControl
{
public:
    NodeBoardControl();
    ~NodeBoardControl() override;

    void setPinMode(uint8_t, uint8_t) override;
    int readDigital(uint8_t) override;
    void restartBoard() override;
};