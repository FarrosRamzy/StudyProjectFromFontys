/**
 * @file my_node_rfid_frame.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.3
 * @date 2026-04-27
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
bool MyNodeRFID::isFrameStartByte(uint8_t byte_in) const
{
    return byte_in == UHF_FRAME_HEADER;
}

/**
 * @brief
 *
 */
void MyNodeRFID::resetFrameBuffer()
{
    frame_index = 0;
    expected_frame_length = 0;
    memset(frame_buffer, 0, sizeof(frame_buffer));
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool MyNodeRFID::appendFrameByte(uint8_t byte_in)
{
    if (frame_index >= RFID_FRAME_BUFFER_SIZE)
    {
        resetFrameBuffer();
        return false;
    }

    frame_buffer[frame_index++] = byte_in;

    // After receiving:
    // [0] Header
    // [1] Type
    // [2] Command
    // [3] PL_MSB
    // [4] PL_LSB

    if (frame_index == 5)
    {
        uint16_t payload_length = ((uint16_t)frame_buffer[3] << 8) | frame_buffer[4];
        expected_frame_length = 7 + payload_length;
        // NOTE - (Header + Type + Command + PL_MSB + PL_LSB + Payload + CRC + End)

        if (expected_frame_length > RFID_FRAME_BUFFER_SIZE)
        {
            resetFrameBuffer();
            return false;
        }
    }

    return true;
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool MyNodeRFID::isFrameComplete() const
{
    if (expected_frame_length == 0)
    {
        return false;
    }
    if (frame_index != expected_frame_length)
    {
        return false;
    }
    return frame_buffer[frame_index - 1] == UHF_FRAME_END;
}

/**
 * @brief
 *
 * @param expected_type
 * @param expected_cmd
 * @return true
 * @return false
 */
bool MyNodeRFID::frameMatches(uint8_t expected_type, uint8_t expected_cmd) const
{
    if (!isValidFrame(frame_index))
    {
        return false;
    }

    return (frame_buffer[1] == expected_type && frame_buffer[2] == expected_cmd);
}
