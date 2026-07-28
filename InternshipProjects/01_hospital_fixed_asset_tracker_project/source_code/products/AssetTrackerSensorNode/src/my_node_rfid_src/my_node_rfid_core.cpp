/**
 * @file my_node_rfid_core.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.3
 * @date 2026-04-10
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_rfid_lib/my_node_rfid.h"

/**
 * @brief Construct a new MyNodeRFID::MyNodeRFID object
 *
 * @param rfid_serial
 * @param rx_pin
 * @param tx_pin
 * @param en_pin
 */
MyNodeRFID::MyNodeRFID(HardwareSerial &rfid_serial, int rx_pin, int tx_pin, int en_pin)
    : my_rfid_serial(rfid_serial), my_rx_pin(rx_pin), my_tx_pin(tx_pin), my_en_pin(en_pin),
      frame_index(0), expected_frame_length(0), my_rfid_power(0), rfid_config_state(RFID_CONFIG_IDLE),
      rfid_config_state_started_at(0), pending_power_cdbm(RFID_POWER_TRANSMIT_20), rfid_config_done(false)
{
    memset(frame_buffer, 0, sizeof(frame_buffer));
}

/**
 * @brief Destroy the MyNodeRFID::MyNodeRFID object
 *
 */
MyNodeRFID::~MyNodeRFID()
{
}

/**
 * @brief
 *
 * @param baudrate
 */
void MyNodeRFID::beginMyNodeRFID(uint32_t baudrate)
{
    pinMode(my_en_pin, OUTPUT);
    enableMyRFID();

    my_rfid_serial.begin(baudrate, SERIAL_8N1, my_rx_pin, my_tx_pin);
    clearBuffer();
    Serial.println("[RFID] Initialized.");
}

/**
 * @brief
 *
 */
void MyNodeRFID::clearBuffer()
{
    while (my_rfid_serial.available() > 0)
    {
        my_rfid_serial.read();
    }

    resetFrameBuffer();
}

/**
 * @brief
 *
 */
void MyNodeRFID::enableMyRFID()
{
    digitalWrite(my_en_pin, HIGH);
}

/**
 * @brief
 *
 */
void MyNodeRFID::disableMyRFID()
{
    digitalWrite(my_en_pin, LOW);
}

/**
 * @brief
 *
 * @param command
 * @param command_length
 * @return true
 * @return false
 */
bool MyNodeRFID::sendCommand(const uint8_t *command, size_t command_length)
{
    if (command == nullptr || command_length == 0)
    {
        return false;
    }

    size_t written_command = my_rfid_serial.write(command, command_length);

    my_rfid_serial.flush();

    return written_command == command_length;
}
