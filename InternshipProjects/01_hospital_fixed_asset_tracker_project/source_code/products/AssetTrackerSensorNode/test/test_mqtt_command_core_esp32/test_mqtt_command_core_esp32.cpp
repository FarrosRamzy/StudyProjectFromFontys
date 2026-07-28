#include <Arduino.h>
#include <string.h>
#include <unity.h>

#include "my_node_core_lib/my_node_mqtt_command_core.h"
#include "../../src/my_node_core_src/my_node_mqtt_command_core.cpp"

void setUp(void) {}
void tearDown(void) {}

void test_valid_blink_command_is_parsed()
{
    const char *json = "{\"command\":\"blink\",\"command_id\":\"CMD1\",\"blink_count\":5,\"interval_ms\":200}";
    MyNodeBlinkCommand cmd;

    bool ok = parseBlinkCommand(json, strlen(json), &cmd);

    TEST_ASSERT_TRUE(ok);
    TEST_ASSERT_EQUAL(NODE_CMD_BLINK, cmd.result);
    TEST_ASSERT_EQUAL_STRING("CMD1", cmd.command_id);
    TEST_ASSERT_EQUAL_UINT8(5, cmd.blink_count);
    TEST_ASSERT_EQUAL_UINT32(200, cmd.interval_ms);
}

void test_invalid_json_is_rejected()
{
    const char *json = "{bad-json";
    MyNodeBlinkCommand cmd;

    bool ok = parseBlinkCommand(json, strlen(json), &cmd);

    TEST_ASSERT_FALSE(ok);
    TEST_ASSERT_EQUAL(NODE_CMD_INVALID_JSON, cmd.result);
}

void test_unknown_command_is_ignored()
{
    const char *json = "{\"command\":\"reset\",\"command_id\":\"CMD2\"}";
    MyNodeBlinkCommand cmd;

    bool ok = parseBlinkCommand(json, strlen(json), &cmd);

    TEST_ASSERT_TRUE(ok);
    TEST_ASSERT_EQUAL(NODE_CMD_IGNORED, cmd.result);
    TEST_ASSERT_EQUAL_STRING("CMD2", cmd.command_id);
}

void test_zero_count_uses_default()
{
    const char *json = "{\"command\":\"blink\",\"blink_count\":0}";
    MyNodeBlinkCommand cmd;

    parseBlinkCommand(json, strlen(json), &cmd);

    TEST_ASSERT_EQUAL_UINT8(NODE_CMD_DEFAULT_BLINK_COUNT, cmd.blink_count);
}

void test_limits_are_clamped()
{
    const char *json = "{\"command\":\"blink\",\"blink_count\":99,\"interval_ms\":10}";
    MyNodeBlinkCommand cmd;

    parseBlinkCommand(json, strlen(json), &cmd);

    TEST_ASSERT_EQUAL_UINT8(NODE_CMD_MAX_BLINK_COUNT, cmd.blink_count);
    TEST_ASSERT_EQUAL_UINT32(NODE_CMD_MIN_INTERVAL_MS, cmd.interval_ms);
}

void setup()
{
    delay(1500);
    UNITY_BEGIN();
    RUN_TEST(test_valid_blink_command_is_parsed);
    RUN_TEST(test_invalid_json_is_rejected);
    RUN_TEST(test_unknown_command_is_ignored);
    RUN_TEST(test_zero_count_uses_default);
    RUN_TEST(test_limits_are_clamped);
    UNITY_END();
}

void loop() {}
