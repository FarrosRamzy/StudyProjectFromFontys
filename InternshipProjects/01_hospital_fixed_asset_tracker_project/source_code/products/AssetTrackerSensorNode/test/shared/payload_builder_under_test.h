#pragma once

#include <ArduinoJson.h>
#include <unity.h>

#include "node_config.h"
#include "my_node_mqtt_lib/my_node_mqtt_payload_builder.h"

#include "../../src/my_node_mqtt_src/mqtt_payload_builder/my_node_mqtt_payload_common.cpp"
#include "../../src/my_node_mqtt_src/mqtt_payload_builder/my_node_mqtt_payload_topics.cpp"
#include "../../src/my_node_mqtt_src/mqtt_payload_builder/my_node_mqtt_payload_asset.cpp"
#include "../../src/my_node_mqtt_src/mqtt_payload_builder/my_node_mqtt_payload_status.cpp"

inline void assertJsonParsed(const char *payload, JsonDocument &doc)
{
    DeserializationError err = deserializeJson(doc, payload);
    TEST_ASSERT_FALSE_MESSAGE(err, "Payload must be valid JSON");
}
