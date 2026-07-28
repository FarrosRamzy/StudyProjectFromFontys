#include <unity.h>

#include "my_node_core_lib/my_node_text_utils.h"
#include "../../src/my_node_core_src/my_node_text_utils.cpp"

void setUp(void) {}
void tearDown(void) {}

void test_hospital_name_becomes_slug()
{
    char output[40] = {0};
    bool ok = buildHospitalId("Imperial Hospital", output, sizeof(output), "default");

    TEST_ASSERT_TRUE(ok);
    TEST_ASSERT_EQUAL_STRING("imperial-hospital", output);
}

void test_extra_symbols_are_cleaned()
{
    char output[40] = {0};
    bool ok = buildHospitalId("  ICU & Medical Center!! ", output, sizeof(output), "default");

    TEST_ASSERT_TRUE(ok);
    TEST_ASSERT_EQUAL_STRING("icu-medical-center", output);
}

void test_empty_name_uses_fallback()
{
    char output[40] = {0};
    bool ok = buildHospitalId("", output, sizeof(output), "hospital-default");

    TEST_ASSERT_TRUE(ok);
    TEST_ASSERT_EQUAL_STRING("hospital-default", output);
}

void test_small_buffer_is_rejected()
{
    char output[8] = {0};
    bool ok = buildHospitalId("Very Long Hospital Name", output, sizeof(output), "default");

    TEST_ASSERT_FALSE(ok);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_hospital_name_becomes_slug);
    RUN_TEST(test_extra_symbols_are_cleaned);
    RUN_TEST(test_empty_name_uses_fallback);
    RUN_TEST(test_small_buffer_is_rejected);
    return UNITY_END();
}
