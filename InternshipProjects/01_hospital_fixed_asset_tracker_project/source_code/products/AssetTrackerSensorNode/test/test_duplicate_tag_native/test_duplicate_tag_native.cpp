#include <unity.h>

#include "my_node_core_lib/my_node_duplicate_tag_filter.h"
#include "../../src/my_node_core_src/my_node_duplicate_tag_filter.cpp"

void setUp(void) {}
void tearDown(void) {}

void test_first_tag_is_not_duplicate()
{
    MyNodeDuplicateTagState state;
    resetDuplicateTagState(&state);

    TEST_ASSERT_FALSE(isDuplicateTagCore(&state, "TAG_A", 1000, 3000));
}

void test_same_tag_inside_window_is_duplicate()
{
    MyNodeDuplicateTagState state;
    resetDuplicateTagState(&state);

    isDuplicateTagCore(&state, "TAG_A", 1000, 3000);
    TEST_ASSERT_TRUE(isDuplicateTagCore(&state, "TAG_A", 2500, 3000));
}

void test_same_tag_after_window_is_not_duplicate()
{
    MyNodeDuplicateTagState state;
    resetDuplicateTagState(&state);

    isDuplicateTagCore(&state, "TAG_A", 1000, 3000);
    TEST_ASSERT_FALSE(isDuplicateTagCore(&state, "TAG_A", 5000, 3000));
}

void test_different_tag_is_not_duplicate()
{
    MyNodeDuplicateTagState state;
    resetDuplicateTagState(&state);

    isDuplicateTagCore(&state, "TAG_A", 1000, 3000);
    TEST_ASSERT_FALSE(isDuplicateTagCore(&state, "TAG_B", 1500, 3000));
}

void test_millis_overflow_window_works()
{
    MyNodeDuplicateTagState state;
    resetDuplicateTagState(&state);

    isDuplicateTagCore(&state, "TAG_A", 4294967290UL, 50);
    TEST_ASSERT_TRUE(isDuplicateTagCore(&state, "TAG_A", 20, 50));
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_first_tag_is_not_duplicate);
    RUN_TEST(test_same_tag_inside_window_is_duplicate);
    RUN_TEST(test_same_tag_after_window_is_not_duplicate);
    RUN_TEST(test_different_tag_is_not_duplicate);
    RUN_TEST(test_millis_overflow_window_works);
    return UNITY_END();
}
