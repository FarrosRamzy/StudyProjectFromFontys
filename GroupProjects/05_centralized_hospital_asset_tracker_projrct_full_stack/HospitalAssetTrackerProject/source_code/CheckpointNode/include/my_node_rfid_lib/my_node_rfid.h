/**
 * @file my_node_rfid.h
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.4
 * @date 2026-04-27
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <stddef.h>
#include "my_node_rfid_lib/interfaces/i_my_node_rfid.h"
#include "my_node_rfid_lib/enum/my_rfid_enum.h"
#include "uhf_rmt_commands.h"
#include "node_config.h"

class MyNodeRFID : public IMyNodeRFID
{
private:
    HardwareSerial &my_rfid_serial;
    int my_rx_pin;
    int my_tx_pin;
    int my_en_pin;

    uint8_t frame_buffer[RFID_FRAME_BUFFER_SIZE];
    size_t frame_index;
    size_t expected_frame_length;

    uint16_t my_rfid_power;

    RFIDConfigState rfid_config_state;
    uint32_t rfid_config_state_started_at;
    uint16_t pending_power_cdbm;
    bool rfid_config_done;

public:
    MyNodeRFID(HardwareSerial &, int, int, int);
    ~MyNodeRFID() override;

    void beginMyNodeRFID(uint32_t) override;
    void enableMyRFID() override;
    void disableMyRFID() override;
    void clearBuffer() override;

    bool readDetectedTag(char *, size_t) override;
    void configureRFID() override;

    void startRFIDConfiguration(uint16_t) override;
    void runRFIDConfiguration() override;
    bool isRFIDConfigurationFinished() const override;

private:
    bool sendCommand(const uint8_t *, size_t);
    bool isValidFrame(size_t) const;
    bool extractEPC(char *, size_t);

    bool readNextByte(uint8_t &);
    bool isFrameStartByte(uint8_t) const;
    void resetFrameBuffer();
    bool appendFrameByte(uint8_t);
    bool isFrameComplete() const;

    bool pollFrame();
    bool waitForResponse(uint8_t, uint8_t, uint32_t);
    bool frameMatches(uint8_t, uint8_t) const;

    bool setTransmitPower(uint16_t);
    bool getTransmitPower(uint16_t &);

    bool sendSetPowerCommandOnly(uint16_t);
    bool isSetPowerSuccessFrame() const;
};