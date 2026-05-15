/**
 * @file my_node_rfid_inventory.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.2
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
bool MyNodeRFID::readDetectedTag(char *epc_buffer, size_t size_of_epc_buffer)
{
    if (epc_buffer == nullptr || size_of_epc_buffer == 0)
    {
        return false;
    }

    clearBuffer();

    if (!sendCommand(UHF_SINGLE_INVENTORY_FRAME, sizeof(UHF_SINGLE_INVENTORY_FRAME)))
    {
        Serial.println("[RFID] failed to send single inventory command.");
        return false;
    }

    uint32_t start_timer = millis();
    while ((uint32_t)(millis() - start_timer) < RFID_TIMEOUT_MS)
    {
        if (!pollFrame())
        {
            delay(1);
            continue;
        }

        if (frame_index >= 7 && frame_buffer[1] == UHF_TYPE_NOTIFICATION &&
            frame_buffer[2] == UHF_CMD_SINGLE_INVENTORY)
        {
            bool ok = extractEPC(epc_buffer, size_of_epc_buffer);
            resetFrameBuffer();
            return ok;
        }

        if (frame_index >= 8 && frame_buffer[1] == UHF_TYPE_RESPONSE &&
            frame_buffer[2] == UHF_CMD_ERROR_RESPONSE)
        {
            uint16_t length_of_payload = ((uint16_t)frame_buffer[3] << 8) | frame_buffer[4];
            if (length_of_payload >= 1 && frame_buffer[5] == UHF_ERR_INVENTORY_FAIL)
            {
                resetFrameBuffer();
                return false;
            }
        }
        resetFrameBuffer();
    }

    return false;
}

/**
 * @brief
 *
 * @param epc_buffer
 * @param epc_buffer_size
 * @return true
 * @return false
 */
bool MyNodeRFID::extractEPC(char *epc_buffer, size_t epc_buffer_size)
{
    if (epc_buffer == nullptr || epc_buffer_size == 0)
    {
        return false;
    }

    // Frame structure assumption for inventory notify:
    // [0] 0xBB
    // [1] type
    // [2] cmd
    // [3] len_hi
    // [4] len_lo
    // [5..] payload
    // [n-2] checksum
    // [n-1] 0x7E

    size_t length = frame_index;

    if (!isValidFrame(length))
    {
        Serial.println("[RFID] Invalid frame");
        return false;
    }

    uint8_t frame_type = frame_buffer[1];
    uint8_t frame_cmd = frame_buffer[2];

    if (frame_type != UHF_TYPE_NOTIFICATION || frame_cmd != UHF_CMD_SINGLE_INVENTORY)
    {
        // Some modules also report inventory under command 0x22 after multi-inventory mode
        // so we still use UHF_CMD_SINGLE_INVENTORY here as the actual notification code.
        Serial.println("[RFID] Not inventory frame");
        return false;
    }

    uint16_t payload_length = ((uint16_t)frame_buffer[3] << 8) | frame_buffer[4];

    if (payload_length == 0)
    {
        return false;
    }

    // Total frame must be at least:
    // header(1) + type(1) + cmd(1) + len(2) + payload + checksum(1) + end(1)
    size_t expected_min_length = 1 + 1 + 1 + 2 + payload_length + 1 + 1;
    if (length < expected_min_length)
    {
        Serial.println("[RFID] frame length mismatch.");
        return false;
    }

    uint8_t checksum = 0;
    for (size_t i = 1; i < length - 2; i++)
    {
        checksum += frame_buffer[i];
    }

    if (checksum != frame_buffer[length - 2])
    {
        Serial.println("[RFID] Checksum mismatch.");
        return false;
    }

    // =========================================================
    // EPC extraction assumption
    //
    // For many modules derived from this protocol, the inventory
    // payload contains metadata before EPC. A common layout is:
    //
    // payload[0] = RSSI
    // payload[1] = PC high
    // payload[2] = PC low
    // payload[3...] = EPC bytes
    //
    // If your actual module layout differs, adjust these offsets.
    // =========================================================

    if (payload_length < 5)
    {
        Serial.println("[RFID] Payload too short.");
        return false;
    }

    const uint8_t *payload = &frame_buffer[5];

    size_t epc_offset = 3;

    if (payload_length <= epc_offset)
    {
        Serial.println("[RFID] Payload too short for EPC.");
        return false;
    }

    size_t epc_length = payload_length - epc_offset;
    if (epc_length == 0)
    {
        Serial.println("[RFID] EPC buffer length is zero.");
        return false;
    }

    if (epc_buffer_size < (epc_length * 2 + 1))
    {
        Serial.println("[RFID] EPC buffer too small.");
        return false;
    }

    for (size_t i = 0; i < epc_length; i++)
    {
        sprintf(&epc_buffer[i * 2], "%02X", payload[epc_offset + i]);
    }

    epc_buffer[epc_length * 2] = '\0';

    Serial.print("[RFID] EPC: ");
    Serial.println(epc_buffer);

    return true;
}