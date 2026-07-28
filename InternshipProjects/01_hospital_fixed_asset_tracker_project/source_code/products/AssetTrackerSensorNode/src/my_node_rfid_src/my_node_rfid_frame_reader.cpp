/**
 * @file my_node_rfid_frame_reader.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-06-03
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_rfid_lib/my_node_rfid.h"

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool MyNodeRFID::pollFrame()
{
    uint8_t byte_in = 0;

    while (readNextByte(byte_in))
    {
        if (frame_index == 0 && !isFrameStartByte(byte_in))
        {
            continue;
        }

        if (!appendFrameByte(byte_in))
        {
            resetFrameBuffer();
            return false;
        }

        if (isFrameComplete())
        {
            if (isValidFrame(frame_index))
            {
                return true;
            }
            resetFrameBuffer();
            return false;
        }

        if (expected_frame_length > 0 && frame_index > expected_frame_length)
        {
            resetFrameBuffer();
            return false;
        }
    }

    return false;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool MyNodeRFID::readNextByte(uint8_t &byte_out)
{
    if (my_rfid_serial.available() <= 0)
    {
        return false;
    }

    byte_out = (uint8_t)my_rfid_serial.read();
    return true;
}

/**
 * @brief
 *
 * @param length
 * @return true
 * @return false
 */
bool MyNodeRFID::isValidFrame(size_t length) const
{
    if (length < 7)
    {
        return false;
    }

    if (frame_buffer[0] != UHF_FRAME_HEADER)
    {
        return false;
    }

    if (frame_buffer[length - 1] != UHF_FRAME_END)
    {
        return false;
    }

    uint16_t payload_length = ((uint16_t)frame_buffer[3] << 8) | frame_buffer[4];

    size_t expected_length = 7 + payload_length;

    if (length != expected_length)
    {
        return false;
    }

    uint8_t calculated_crc = 0;

    // CRC/checksum is the low byte of the sum from Type to last payload byte.
    //  So: index 1 until byte before CRC.

    for (size_t i = 1; i < length - 2; i++)
    {
        calculated_crc += frame_buffer[i];
    }

    uint8_t received_crc = frame_buffer[length - 2];

    if (calculated_crc != received_crc)
    {
        return false;
    }

    return true;
}

/**
 * @brief
 *
 * @param expected_type
 * @param expected_cmd
 * @param timeout_ms
 * @return true
 * @return false
 */
bool MyNodeRFID::waitForResponse(uint8_t expected_type, uint8_t expected_cmd, uint32_t timeout_ms)
{
    uint32_t start_time = millis();

    while ((uint32_t)(millis() - start_time) < timeout_ms)
    {
        if (!pollFrame())
        {
            continue;
        }

        if (frameMatches(expected_type, expected_cmd))
        {
            resetFrameBuffer();
            return true;
        }
        resetFrameBuffer();
    }
    return false;
}
