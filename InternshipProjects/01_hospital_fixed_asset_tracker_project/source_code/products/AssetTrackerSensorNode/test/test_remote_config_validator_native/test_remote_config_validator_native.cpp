#include <unity.h>

#include "my_node_core_lib/my_node_remote_config_validator.h"
#include "../../src/my_node_core_src/my_node_remote_config_validator.cpp"

MyNodeRemoteConfigLite checkpointConfig()
{
    return {
        "CHECKPOINT",
        "Imperial Hospital",
        "ICU Room 1",
        "broker.hivemq.com",
        1883,
        true,
    };
}

void setUp(void) {}

void tearDown(void) {}

void test_valid_checkpoint_config_is_accepted()
{
    TEST_ASSERT_TRUE(isProvisionedConfigValid(checkpointConfig()));
}

void test_valid_registration_config_allows_empty_room()
{
    MyNodeRemoteConfigLite config = {
        "REGISTRATION",
        "Imperial Hospital",
        "",
        "broker.hivemq.com",
        1883,
        true,
    };

    TEST_ASSERT_TRUE(isProvisionedConfigValid(config));
}

void test_checkpoint_config_requires_room()
{
    MyNodeRemoteConfigLite config = checkpointConfig();
    config.room_name = "";

    TEST_ASSERT_FALSE(isProvisionedConfigValid(config));
}

void test_config_rejects_missing_mqtt_host()
{
    MyNodeRemoteConfigLite config = checkpointConfig();
    config.mqtt_host = "";

    TEST_ASSERT_FALSE(isProvisionedConfigValid(config));
}

void test_config_rejects_unprovisioned_response()
{
    MyNodeRemoteConfigLite config = checkpointConfig();
    config.is_provisioned = false;

    TEST_ASSERT_FALSE(isProvisionedConfigValid(config));
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_valid_checkpoint_config_is_accepted);
    RUN_TEST(test_valid_registration_config_allows_empty_room);
    RUN_TEST(test_checkpoint_config_requires_room);
    RUN_TEST(test_config_rejects_missing_mqtt_host);
    RUN_TEST(test_config_rejects_unprovisioned_response);

    return UNITY_END();
}
