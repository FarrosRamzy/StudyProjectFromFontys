#include <unity.h>

#include "my_node_core_lib/my_node_state_decision.h"
#include "../../src/my_node_core_src/my_node_state_decision.cpp"

void setUp(void) {}

void tearDown(void) {}

void test_wifi_disconnected_tries_wifi()
{
    TEST_ASSERT_EQUAL(ACTION_TRY_WIFI,
        decideNextNodeAction(false, false, false, false));
}

void test_unprovisioned_tries_provisioning()
{
    TEST_ASSERT_EQUAL(ACTION_TRY_PROVISION,
        decideNextNodeAction(true, false, false, false));
}

void test_mqtt_disconnected_tries_mqtt()
{
    TEST_ASSERT_EQUAL(ACTION_TRY_MQTT,
        decideNextNodeAction(true, true, false, false));
}

void test_heartbeat_due_publishes_heartbeat()
{
    TEST_ASSERT_EQUAL(ACTION_PUBLISH_HEARTBEAT,
        decideNextNodeAction(true, true, true, true));
}

void test_ready_node_reads_rfid()
{
    TEST_ASSERT_EQUAL(ACTION_READ_RFID,
        decideNextNodeAction(true, true, true, false));
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_wifi_disconnected_tries_wifi);
    RUN_TEST(test_unprovisioned_tries_provisioning);
    RUN_TEST(test_mqtt_disconnected_tries_mqtt);
    RUN_TEST(test_heartbeat_due_publishes_heartbeat);
    RUN_TEST(test_ready_node_reads_rfid);

    return UNITY_END();
}
