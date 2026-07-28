/**
 * @file node_board_control.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-14
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_manager_lib/node_board_control.h"

/**
 * @brief Construct a new Node Board Control:: Node Board Control object
 * 
 */
NodeBoardControl::NodeBoardControl()
{
}

/**
 * @brief Destroy the Node Board Control:: Node Board Control object
 * 
 */
NodeBoardControl::~NodeBoardControl()
{
}

/**
 * @brief 
 * 
 * @param pin 
 * @param mode 
 */
void NodeBoardControl::setPinMode(uint8_t pin, uint8_t mode)
{
    pinMode(pin, mode);
}

/**
 * @brief 
 * 
 * @param pin 
 * @return int 
 */
int NodeBoardControl::readDigital(uint8_t pin)
{
    return digitalRead(pin);
}

/**
 * @brief 
 * 
 */
void NodeBoardControl::restartBoard()
{
    ESP.restart();
}
