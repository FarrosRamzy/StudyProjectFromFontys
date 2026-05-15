/**
 * @file node_reset_button.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.2
 * @date 2026-04-15
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_manager_lib/node_manager.h"

/**
 * @brief 
 * 
 */
void NodeManager::setupNetConfigResetButton()
{
    my_board.setPinMode(CONFIG_RESET_BUTTON_PIN, INPUT_PULLUP);
}

/**
 * @brief 
 * 
 */
void NodeManager::handleConfigResetButton()
{
    bool pressed = (my_board.readDigital(CONFIG_RESET_BUTTON_PIN) == LOW);
    uint32_t now = my_clock.millisNow();

    if (!pressed)
    {
        if (reset_button_was_pressed)
        {
            Serial.println("[SYSTEM] Reset button released.");
        }
        
        reset_button_was_pressed = false;
        reset_button_triggered = false;
        reset_button_press_start = 0;
        return;
    }
    
    if (!reset_button_was_pressed)
    {
        reset_button_was_pressed = true;
        reset_button_triggered = false;
        reset_button_press_start = now;
        Serial.println("[SYSTEM] Reset button pressed.");
        return;
    }
    
    if (reset_button_triggered)
    {
        return;
    }
    
    
    if ((uint32_t)(now - reset_button_press_start) < CONFIG_RESET_HOLD_MS)
    {
        return;
    }
    
    reset_button_triggered = true;
    Serial.println("[SYSTEM] Reset button hold detected. Clearing config...");
    
    sayGoodbye();
    
    my_node_net_config.resetConfiguration();
    
    
    Serial.println("[SYSTEM] Restarting ...");
    my_board.restartBoard();
}