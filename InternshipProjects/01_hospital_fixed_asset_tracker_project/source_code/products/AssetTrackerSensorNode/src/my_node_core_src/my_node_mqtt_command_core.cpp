/**
 * @file my_node_mqtt_command_core.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-06-25
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_core_lib/my_node_mqtt_command_core.h"

#include <ArduinoJson.h>
#include <string.h>

static void resetOutput(MyNodeBlinkCommand *output)
{
    output->result = NODE_CMD_INVALID_JSON;
    output->command_id[0] = '\0';
    output->blink_count = NODE_CMD_DEFAULT_BLINK_COUNT;
    output->interval_ms = NODE_CMD_DEFAULT_INTERVAL_MS;
}

static void copyCommandId(MyNodeBlinkCommand *output, const char *command_id)
{
    if (command_id == nullptr)
    {
        return;
    }

    strncpy(output->command_id, command_id, NODE_CMD_ID_SIZE - 1);
    output->command_id[NODE_CMD_ID_SIZE - 1] = '\0';
}

bool parseBlinkCommand(
    const char *payload,
    size_t length,
    MyNodeBlinkCommand *output)
{
    if (output == nullptr)
    {
        return false;
    }

    resetOutput(output);

    if (payload == nullptr || length == 0)
    {
        return false;
    }

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, payload, length);

    if (error)
    {
        output->result = NODE_CMD_INVALID_JSON;
        return false;
    }

    const char *command = doc["command"] | "";
    const char *command_id = doc["command_id"] | "";
    copyCommandId(output, command_id);

    if (strcmp(command, "blink") != 0)
    {
        output->result = NODE_CMD_IGNORED;
        return true;
    }

    uint8_t count = doc["blink_count"] | NODE_CMD_DEFAULT_BLINK_COUNT;
    uint32_t interval = doc["interval_ms"] | NODE_CMD_DEFAULT_INTERVAL_MS;

    if (count == 0)
    {
        count = NODE_CMD_DEFAULT_BLINK_COUNT;
    }
    if (count > NODE_CMD_MAX_BLINK_COUNT)
    {
        count = NODE_CMD_MAX_BLINK_COUNT;
    }
    if (interval < NODE_CMD_MIN_INTERVAL_MS)
    {
        interval = NODE_CMD_MIN_INTERVAL_MS;
    }

    output->result = NODE_CMD_BLINK;
    output->blink_count = count;
    output->interval_ms = interval;
    return true;
}
