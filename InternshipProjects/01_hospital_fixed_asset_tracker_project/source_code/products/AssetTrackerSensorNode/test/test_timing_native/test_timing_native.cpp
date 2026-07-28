#include <unity.h>

#include "my_node_core_lib/my_node_timing.h"
#include "../../src/my_node_core_src/my_node_timing.cpp"

void setUp(void) {}

void tearDown(void) {}

void test_interval_is_due_at_exact_time()
{
    TEST_ASSERT_TRUE(isIntervalDue(30000, 0, 30000));
}

void test_interval_is_not_due_before_time()
{
    TEST_ASSERT_FALSE(isIntervalDue(29999, 0, 30000));
}

void test_interval_is_due_after_time()
{
    TEST_ASSERT_TRUE(isIntervalDue(45000, 10000, 30000));
}

void test_interval_handles_millis_overflow()
{
    uint32_t last_ms = 4294967290UL;
    uint32_t now_ms = 20;

    TEST_ASSERT_TRUE(isIntervalDue(now_ms, last_ms, 25));
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_interval_is_due_at_exact_time);
    RUN_TEST(test_interval_is_not_due_before_time);
    RUN_TEST(test_interval_is_due_after_time);
    RUN_TEST(test_interval_handles_millis_overflow);

    return UNITY_END();
}
