/**
 * @file uhf_rmt_commands.h
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.2
 * @date 2026-04-10
 *
 * @copyright Copyright (c) 2026
 *
 */

/*
 * EL-UHF-RMT01 Command Protocol
 * Frame format:
 * [0] Header (0xBB)
 * [1] Type
 * [2] Command
 * [3-4] Parameter Length
 * [n] Parameters
 * [n+1] CRC
 * [n+2] End (0x7E)
 */

#pragma once
#include <stdint.h>

// ----------------------
// Frame markers
// ----------------------
#define UHF_FRAME_HEADER 0xBB
#define UHF_FRAME_END 0x7E

// ----------------------
// Frame types
// ----------------------
#define UHF_TYPE_COMMAND 0x00
#define UHF_TYPE_RESPONSE 0x01
#define UHF_TYPE_NOTIFICATION 0x02

// ----------------------
// Core command codes
// ----------------------
#define UHF_CMD_GET_INFO 0x03
#define UHF_CMD_SINGLE_INVENTORY 0x22
#define UHF_CMD_MULTI_INVENTORY 0x27
#define UHF_CMD_STOP_MULTI_INVENTORY 0x28

#define UHF_CMD_READ_TAG 0x39
#define UHF_CMD_WRITE_TAG 0x49
#define UHF_CMD_LOCK_TAG 0x82
#define UHF_CMD_KILL_TAG 0x65

// ----------------------
// Configuration commands
// ----------------------
#define UHF_CMD_SET_BAUD 0x11
#define UHF_CMD_SET_REGION 0x07
#define UHF_CMD_SET_CHANNEL 0xAB
#define UHF_CMD_GET_CHANNEL 0xAA
#define UHF_CMD_SET_QUERY 0x0E
#define UHF_CMD_GET_QUERY 0x0D
#define UHF_CMD_SET_POWER 0xB6
#define UHF_CMD_GET_POWER 0xB7

// ----------------------
// Sleep / IO
// ----------------------
#define UHF_CMD_SLEEP 0x17
#define UHF_CMD_IDLE_SLEEP 0x1D
#define UHF_CMD_IO_CONTROL 0x1A

// ----------------------
// Common response/error indicators
// ----------------------
#define UHF_CMD_ERROR_RESPONSE 0xFF
#define UHF_ERR_INVENTORY_FAIL 0x15
#define UHF_ERR_WRONG_PASSWORD 0x16
#define UHF_ERR_READ_FAIL 0x09
#define UHF_ERR_WRITE_FAIL 0x10
#define UHF_ERR_LOCK_FAIL 0x13
#define UHF_ERR_KILL_FAIL 0x12

// ======================================================
// Checksum helper
// Checksum = low byte of the sum from Type to last Param
// ======================================================
#define UHF_CHECKSUM6(type, cmd, len_msb, len_lsb, p0, p1) \
    ((uint8_t)(((type) + (cmd) + (len_msb) + (len_lsb) + (p0) + (p1)) & 0xFF))

#define UHF_CHECKSUM7(type, cmd, len_msb, len_lsb, p0, p1, p2) \
    ((uint8_t)(((type) + (cmd) + (len_msb) + (len_lsb) + (p0) + (p1) + (p2)) & 0xFF))

// ======================================================
// Ready-to-use frames
// ======================================================

// ----------------------------------
// Single inventory
// BB 00 22 00 00 22 7E
// ----------------------------------
static const uint8_t UHF_SINGLE_INVENTORY_FRAME[] = {
    UHF_FRAME_HEADER,
    UHF_TYPE_COMMAND,
    UHF_CMD_SINGLE_INVENTORY,
    0x00,
    0x00,
    0x22,
    UHF_FRAME_END};

// ----------------------------------
// Multiple inventory
// Example with polling count = 0x0010
// BB 00 27 00 03 22 00 10 5C 7E
//
// Parameter meanings:
// [0] 0x22 reserved/protocol byte
// [1] polling count MSB
// [2] polling count LSB
// ----------------------------------
#define UHF_MULTI_RESERVED_BYTE 0x22
#define UHF_MULTI_COUNT_MSB 0x00
#define UHF_MULTI_COUNT_LSB 0x10

static const uint8_t UHF_MULTI_INVENTORY_FRAME[] = {
    UHF_FRAME_HEADER,
    UHF_TYPE_COMMAND,
    UHF_CMD_MULTI_INVENTORY,
    0x00,
    0x03,
    UHF_MULTI_RESERVED_BYTE,
    UHF_MULTI_COUNT_MSB,
    UHF_MULTI_COUNT_LSB,
    UHF_CHECKSUM7(UHF_TYPE_COMMAND,
                  UHF_CMD_MULTI_INVENTORY,
                  0x00, 0x03,
                  UHF_MULTI_RESERVED_BYTE,
                  UHF_MULTI_COUNT_MSB,
                  UHF_MULTI_COUNT_LSB),
    UHF_FRAME_END};

// ----------------------------------
// Stop multiple inventory
// BB 00 28 00 00 28 7E
// ----------------------------------
static const uint8_t UHF_STOP_MULTI_INVENTORY_FRAME[] = {
    UHF_FRAME_HEADER,
    UHF_TYPE_COMMAND,
    UHF_CMD_STOP_MULTI_INVENTORY,
    0x00,
    0x00,
    0x28,
    UHF_FRAME_END};

// ----------------------------------
// Get module info
// Example form documented with 1-byte parameter = 0x00
// ----------------------------------
static const uint8_t UHF_GET_INFO_FRAME[] = {
    UHF_FRAME_HEADER,
    UHF_TYPE_COMMAND,
    UHF_CMD_GET_INFO,
    0x00,
    0x01,
    0x00,
    UHF_CHECKSUM6(UHF_TYPE_COMMAND,
                  UHF_CMD_GET_INFO,
                  0x00, 0x01,
                  0x00, 0x00),
    UHF_FRAME_END};
