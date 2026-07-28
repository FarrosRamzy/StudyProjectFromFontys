#include <Arduino.h>
#include <unity.h>

#include "../shared/payload_builder_under_test.h"

static const char *HOSPITAL_ID = "HOSP_1";
static const char *DEVICE_ID = "NODE_1";

void setUp(void) {}
void tearDown(void) {}

void test_detection_topic_is_correct()
{
    char topic[SIZE_OF_TOPIC] = {0};

    TEST_ASSERT_TRUE(buildDetectionTopic(
        HOSPITAL_ID, DEVICE_ID, topic, sizeof(topic)));

    TEST_ASSERT_EQUAL_STRING(
        "hospital/HOSP_1/nodes/NODE_1/rfid/detected", topic);
}

void test_registration_topic_is_correct()
{
    char topic[SIZE_OF_TOPIC] = {0};

    TEST_ASSERT_TRUE(buildRegistrationTopic(
        HOSPITAL_ID, DEVICE_ID, topic, sizeof(topic)));

    TEST_ASSERT_EQUAL_STRING(
        "hospital/HOSP_1/nodes/NODE_1/rfid/asset-registration", topic);
}

void test_heartbeat_topic_is_correct()
{
    char topic[SIZE_OF_TOPIC] = {0};

    TEST_ASSERT_TRUE(buildHeartbeatTopic(
        HOSPITAL_ID, DEVICE_ID, topic, sizeof(topic)));

    TEST_ASSERT_EQUAL_STRING(
        "hospital/HOSP_1/nodes/NODE_1/heartbeat", topic);
}

void test_status_topic_is_correct()
{
    char topic[SIZE_OF_TOPIC] = {0};

    TEST_ASSERT_TRUE(buildStatusTopic(
        HOSPITAL_ID, DEVICE_ID, topic, sizeof(topic)));

    TEST_ASSERT_EQUAL_STRING(
        "hospital/HOSP_1/nodes/NODE_1/status", topic);
}

void test_command_blink_topic_is_correct()
{
    char topic[SIZE_OF_TOPIC] = {0};

    TEST_ASSERT_TRUE(buildCommandBlinkTopic(
        HOSPITAL_ID, DEVICE_ID, topic, sizeof(topic)));

    TEST_ASSERT_EQUAL_STRING(
        "hospital/HOSP_1/nodes/NODE_1/commands/blink", topic);
}

void setup()
{
    delay(1500);
    UNITY_BEGIN();

    RUN_TEST(test_detection_topic_is_correct);
    RUN_TEST(test_registration_topic_is_correct);
    RUN_TEST(test_heartbeat_topic_is_correct);
    RUN_TEST(test_status_topic_is_correct);
    RUN_TEST(test_command_blink_topic_is_correct);

    UNITY_END();
}

void loop() {}
