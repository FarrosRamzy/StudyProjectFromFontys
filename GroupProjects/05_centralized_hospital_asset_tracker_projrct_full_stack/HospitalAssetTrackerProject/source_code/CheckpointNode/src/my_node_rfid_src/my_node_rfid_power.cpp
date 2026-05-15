/**
 * @file my_node_rfid_power.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-06
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "my_node_rfid_lib/my_node_rfid.h"

/**
 * @brief
 *
 * @param power_cdbm
 * @return true
 * @return false
 */
bool MyNodeRFID::sendSetPowerCommandOnly(uint16_t power_cdbm)
{
    uint8_t power_hi = (power_cdbm >> 8) & 0xFF;
    uint8_t power_lo = power_cdbm & 0xFF;

    uint8_t frame[] = {
        UHF_FRAME_HEADER,
        UHF_TYPE_COMMAND,
        UHF_CMD_SET_POWER,
        0x00,
        0x02,
        power_hi,
        power_lo,
        (uint8_t)((UHF_TYPE_COMMAND + UHF_CMD_SET_POWER + 0x00 + 0x02 +
                   power_hi + power_lo) &
                  0xFF),
        UHF_FRAME_END};

    Serial.println("[RFID] SET_POWER TX: ");

    for (size_t i = 0; i < sizeof(frame); i++)
    {
        /* code */
        if (frame[i] < 0x10)
        {
            /* code */
            Serial.print("0");
        }

        Serial.print(frame[i], HEX);
        Serial.print(" ");
    }

    Serial.println();

    return sendCommand(frame, sizeof(frame));
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool MyNodeRFID::isSetPowerSuccessFrame() const
{
    if (!isValidFrame(frame_index))
    {
        /* code */
        return false;
    }

    uint8_t rx_type = frame_buffer[1];
    uint8_t rx_cmd = frame_buffer[2];

    if (rx_type != UHF_TYPE_RESPONSE)
    {
        /* code */
        return false;
    }

    if (rx_cmd != UHF_CMD_SET_POWER)
    {
        /* code */
        return false;
    }

    uint16_t payload_length = ((uint16_t)frame_buffer[3] << 8) | frame_buffer[4];

    if (payload_length == 0)
    {
        return true;
    }

    if (payload_length >= 1 && frame_buffer[5] == 0x00)
    {
        /* code */
        return true;
    }

    Serial.print("[RFID] SET_POWER error status: 0x");
    Serial.println(frame_buffer[5], HEX);

    return false;
}

/**
 * @brief
 *
 * @param power_cdbm
 * @return true
 * @return false
 */
bool MyNodeRFID::setTransmitPower(uint16_t power_cdbm)
{
    if (!sendSetPowerCommandOnly(power_cdbm))
    {
        /* code */
        Serial.println("[RFID] SET_POWER send failed.");
        return false;
    }

    if (!waitForResponse(UHF_TYPE_RESPONSE, UHF_CMD_SET_POWER, RFID_CONFIG_RESPONSE_TIMEOUT_MS))
    {
        /* code */
        Serial.println("[RFID] SET_POWER send failed.");
        return false;
    }

    Serial.println("[RFID] Power set to raw value: ");
    Serial.print(power_cdbm);

    return true;
}

/**
 * @brief
 *
 * @param power_cdbm
 * @return true
 * @return false
 */
bool MyNodeRFID::getTransmitPower(uint16_t &power_cdbm)
{
    static const uint8_t frame[] = {
        UHF_FRAME_HEADER,
        UHF_TYPE_COMMAND,
        UHF_CMD_GET_POWER,
        0x00, 0x00,
        UHF_CMD_GET_POWER,
        UHF_FRAME_END};

    clearBuffer();

    if (!sendCommand(frame, sizeof(frame)))
    {
        Serial.println("[RFID] Failed to send GET_POWER");
        return false;
    }

    uint32_t start_time = millis();
    while ((uint32_t)(millis() - start_time) < RFID_TIMEOUT_MS)
    {
        if (!pollFrame())
        {
            delay(1);
            continue;
        }

        if (!isValidFrame(frame_index))
        {
            resetFrameBuffer();
            continue;
        }

        if (frame_buffer[1] == UHF_TYPE_RESPONSE && frame_buffer[2] == UHF_CMD_GET_POWER)
        {
            uint16_t payload_length = ((uint16_t)frame_buffer[3] << 8) | frame_buffer[4];

            if (payload_length == 2)
            {
                power_cdbm = ((uint16_t)frame_buffer[5] << 8) | frame_buffer[6];
                resetFrameBuffer();
                return true;
            }
        }

        resetFrameBuffer();
    }

    return false;
}