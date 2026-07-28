/**
 * @file my_node_rfid_config.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-10
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_rfid_lib/my_node_rfid.h"

/**
 * @brief
 *
 */
void MyNodeRFID::configureRFID()
{
    startRFIDConfiguration(RFID_POWER_TRANSMIT_2);
}

/**
 * @brief
 *
 * @param power_cdbm
 */
void MyNodeRFID::startRFIDConfiguration(uint16_t power_cdbm)
{
    pending_power_cdbm = power_cdbm;
    rfid_config_done = false;
    rfid_config_state = RFID_CONFIG_WAIT_READER_READY;
    rfid_config_state_started_at = millis();

    clearBuffer();

    Serial.println("[RFID] Non-blocking config started.");
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool MyNodeRFID::isRFIDConfigurationFinished() const
{
    return rfid_config_state == RFID_CONFIG_DONE || rfid_config_state == RFID_CONFIG_FAILED;
}

/**
 * @brief
 *
 */
void MyNodeRFID::runRFIDConfiguration()
{
    uint32_t now = millis();

    switch (rfid_config_state)
    {
    case RFID_CONFIG_IDLE:
    case RFID_CONFIG_DONE:
    case RFID_CONFIG_FAILED:
        return;

    case RFID_CONFIG_WAIT_READER_READY:
        if ((uint32_t)(now - rfid_config_state_started_at) >= RFID_READER_READY_DELAY_MS)
        {
            rfid_config_state = RFID_CONFIG_SEND_STOP_INVENTORY;
        }
        return;

    case RFID_CONFIG_SEND_STOP_INVENTORY:
        Serial.println("[RFID] Sending STOP inventory before config.");
        clearBuffer();

        sendCommand(UHF_STOP_MULTI_INVENTORY_FRAME, sizeof(UHF_STOP_MULTI_INVENTORY_FRAME));

        rfid_config_state = RFID_CONFIG_WAIT_AFTER_STOP;
        rfid_config_state_started_at = now;
        return;

    case RFID_CONFIG_WAIT_AFTER_STOP:
        if ((uint32_t)(now - rfid_config_state_started_at) >= RFID_READER_READY_DELAY_MS)
        {
            clearBuffer();
            rfid_config_state = RFID_CONFIG_SEND_SET_POWER;
        }
        return;
    case RFID_CONFIG_SEND_SET_POWER:
        Serial.println("[RFID] Sending SET_POWER command.");

        if (!sendSetPowerCommandOnly(pending_power_cdbm))
        {
            clearBuffer();
            Serial.println("[RFID] SET_POWER send failed.");
            rfid_config_state = RFID_CONFIG_FAILED;
            return;
        }
        rfid_config_state = RFID_CONFIG_WAIT_SET_POWER_RESPONSE;
        rfid_config_state_started_at = now;
        return;
    case RFID_CONFIG_WAIT_SET_POWER_RESPONSE:
        if (pollFrame())
        {
            if (isSetPowerSuccessFrame())
            {
                Serial.println("[RFID] SET_POWER success.");
                resetFrameBuffer();

                rfid_config_done = true;
                rfid_config_state = RFID_CONFIG_DONE;
                return;
            }

            Serial.println("[RFID] SET_POWER received non-matching frame.");
            resetFrameBuffer();
        }

        if ((uint32_t)(now - rfid_config_state_started_at) >= RFID_CONFIG_RESPONSE_TIMEOUT_MS)
        {
            Serial.println("[RFID] SET_POWER timeout. Continuing with default reader power.");
            rfid_config_state = RFID_CONFIG_FAILED;
        }

        return;
    }
}
