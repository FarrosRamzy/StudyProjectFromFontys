/**
 * @file my_rfid_enum.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-06
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#pragma once

#include "node_config.h"

enum RFIDConfigState
{
    RFID_CONFIG_IDLE,
    RFID_CONFIG_WAIT_READER_READY,
    RFID_CONFIG_SEND_STOP_INVENTORY,
    RFID_CONFIG_WAIT_AFTER_STOP,
    RFID_CONFIG_SEND_SET_POWER,
    RFID_CONFIG_WAIT_SET_POWER_RESPONSE,
    RFID_CONFIG_DONE,
    RFID_CONFIG_FAILED
};
