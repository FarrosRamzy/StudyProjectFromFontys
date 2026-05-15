/**
 * @file i_node_board_control.h
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

 class INodeBoardControl
 {
 public:
    virtual ~INodeBoardControl() {}

    virtual void setPinMode(uint8_t, uint8_t) = 0;
    virtual int readDigital(uint8_t) = 0;
    virtual void restartBoard() = 0;
 };