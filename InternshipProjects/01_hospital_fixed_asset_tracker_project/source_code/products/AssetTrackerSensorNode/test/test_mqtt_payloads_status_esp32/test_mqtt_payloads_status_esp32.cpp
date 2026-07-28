#include <Arduino.h>
#include <unity.h>

#include "../shared/payload_builder_under_test.h"

static const char *HOSPITAL_ID = "HOSP_1";
static const char *HOSPITAL_NAME = "Hospital One";
static const char *DEVICE_ID = "NODE_1";
static const char *ROOM_NAME = "ICU";
static const char *TIMESTAMP = "2026-05-29T10:00:00+07:00";

void setUp(void) {}
void tearDown(void) {}

void test_heartbeat_payload_contains_expected_fields()
{
    char payload[SIZE_OF_PAYLOAD] = {0};

    TEST_ASSERT_TRUE(buildHeartbeatPayload(
        HOSPITAL_ID, HOSPITAL_NAME, DEVICE_ID,
        ROOM_NAME, TIMESTAMP, payload, sizeof(payload)));

    JsonDocument doc;
    assertJsonParsed(payload, doc);

    TEST_ASSERT_EQUAL_STRING(HOSPITAL_ID, doc["hospital_id"]);
    TEST_ASSERT_EQUAL_STRING(HOSPITAL_NAME, doc["hospital_name"]);
    TEST_ASSERT_EQUAL_STRING(ROOM_NAME, doc["room_name"]);
    TEST_ASSERT_EQUAL_STRING(DEVICE_ID, doc["device_id"]);
    TEST_ASSERT_EQUAL_STRING("OK", doc["status"]);
    TEST_ASSERT_EQUAL_STRING("heartbeat", doc["message"]);
    TEST_ASSERT_EQUAL_STRING(TIMESTAMP, doc["timestamp"]);
}

void test_status_payload_contains_expected_fields()
{
    char payload[SIZE_OF_PAYLOAD] = {0};

    TEST_ASSERT_TRUE(buildStatusPayload(
        HOSPITAL_ID, HOSPITAL_NAME, DEVICE_ID, ROOM_NAME,
        "Node started", "ONLINE", TIMESTAMP, payload, sizeof(payload)));

    JsonDocument doc;
    assertJsonParsed(payload, doc);

    TEST_ASSERT_EQUAL_STRING(HOSPITAL_ID, doc["hospital_id"]);
    TEST_ASSERT_EQUAL_STRING(HOSPITAL_NAME, doc["hospital_name"]);
    TEST_ASSERT_EQUAL_STRING(ROOM_NAME, doc["room_name"]);
    TEST_ASSERT_EQUAL_STRING(DEVICE_ID, doc["device_id"]);
    TEST_ASSERT_EQUAL_STRING("Node started", doc["message"]);
    TEST_ASSERT_EQUAL_STRING("ONLINE", doc["status"]);
    TEST_ASSERT_EQUAL_STRING(TIMESTAMP, doc["timestamp"]);
}

void setup()
{
    delay(1500);
    UNITY_BEGIN();

    RUN_TEST(test_heartbeat_payload_contains_expected_fields);
    RUN_TEST(test_status_payload_contains_expected_fields);

    UNITY_END();
}

void loop() {}
