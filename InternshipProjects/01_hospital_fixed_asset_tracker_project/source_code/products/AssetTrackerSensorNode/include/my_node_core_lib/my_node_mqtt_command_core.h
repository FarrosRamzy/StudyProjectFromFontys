#pragma once

#include <stdint.h>
#include <stddef.h>

#define NODE_CMD_DEFAULT_BLINK_COUNT 3
#define NODE_CMD_DEFAULT_INTERVAL_MS 150
#define NODE_CMD_MAX_BLINK_COUNT 20
#define NODE_CMD_MIN_INTERVAL_MS 50

#define NODE_CMD_ID_SIZE 40

enum MyNodeCommandResult
{
    NODE_CMD_INVALID_JSON,
    NODE_CMD_IGNORED,
    NODE_CMD_BLINK
};

struct MyNodeBlinkCommand
{
    MyNodeCommandResult result;
    char command_id[NODE_CMD_ID_SIZE];
    uint8_t blink_count;
    uint32_t interval_ms;
};

bool parseBlinkCommand(
    const char *payload,
    size_t length,
    MyNodeBlinkCommand *output);
