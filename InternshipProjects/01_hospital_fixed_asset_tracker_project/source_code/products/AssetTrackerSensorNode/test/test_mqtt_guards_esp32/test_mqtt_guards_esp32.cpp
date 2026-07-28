#include <Arduino.h>
#include <unity.h>

#include "../shared/payload_builder_under_test.h"

void setUp(void) {}
void tearDown(void) {}

void test_required_text_rejects_bad_values()
{
    TEST_ASSERT_FALSE(hasRequiredText(nullptr));
    TEST_ASSERT_FALSE(hasRequiredText(""));
    TEST_ASSERT_TRUE(hasRequiredText("abc"));
}

void test_detection_topic_rejects_missing_hospital_id()
{
    char topic[SIZE_OF_TOPIC] = {0};

    TEST_ASSERT_FALSE(buildDetectionTopic(
        "", "NODE_1", topic, sizeof(topic)));
}

void test_detection_topic_rejects_missing_device_id()
{
    char topic[SIZE_OF_TOPIC] = {0};

    TEST_ASSERT_FALSE(buildDetectionTopic(
        "HOSP_1", "", topic, sizeof(topic)));
}

void test_detection_payload_rejects_missing_tag_id()
{
    char payload[SIZE_OF_PAYLOAD] = {0};

    TEST_ASSERT_FALSE(buildDetectionPayload(
        "HOSP_1", "General Hospital", "NODE_1", "ICU",
        "", "2026-05-29T10:00:00+07:00",
        payload, sizeof(payload)));
}

void test_status_payload_rejects_missing_status()
{
    char payload[SIZE_OF_PAYLOAD] = {0};

    TEST_ASSERT_FALSE(buildStatusPayload(
        "HOSP_1", "General Hospital", "NODE_1", "ICU",
        "Hello!", "", "2026-05-29T10:00:00+07:00",
        payload, sizeof(payload)));
}

void setup()
{
    delay(1500);
    UNITY_BEGIN();

    RUN_TEST(test_required_text_rejects_bad_values);
    RUN_TEST(test_detection_topic_rejects_missing_hospital_id);
    RUN_TEST(test_detection_topic_rejects_missing_device_id);
    RUN_TEST(test_detection_payload_rejects_missing_tag_id);
    RUN_TEST(test_status_payload_rejects_missing_status);

    UNITY_END();
}

void loop() {}
