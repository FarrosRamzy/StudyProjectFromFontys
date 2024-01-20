#include "../product/MyStack.hpp"
#include <gtest/gtest.h>

class MyStackTest : public ::testing::Test
{
protected:
    MyStack *my_new_stack;

    void SetUp() override
    {
        my_new_stack = new MyStack(sizeof(int));
    }

    void TearDown() override
    {
        delete my_new_stack;
    }
};

TEST_F(MyStackTest, testPushObject)
{
    int my_new_val = 86;
    ASSERT_EQ(0, my_new_stack->pushObject(&my_new_val));
    ASSERT_EQ(1, my_new_stack->numberOfElements());   
}

TEST_F(MyStackTest, testPushPopObject)
{
    int my_new_val = 86;
    int my_popped_value;

    ASSERT_EQ(0, my_new_stack->pushObject(&my_new_val));
    ASSERT_EQ(1, my_new_stack->numberOfElements());

    ASSERT_EQ(0, my_new_stack->popObject(&my_popped_value));   
    ASSERT_EQ(-1, my_new_stack->numberOfElements());   
    ASSERT_EQ(my_new_val, my_popped_value);   
}

TEST_F(MyStackTest, testMultiplePushPopObject) {
    int my_values[] = {1, 2, 3, 4};

    for (int i = 0; i < 4; ++i) {
        ASSERT_EQ(0, my_new_stack->pushObject(&my_values[i]));
        ASSERT_EQ(i + 1, my_new_stack->numberOfElements());
    }

    for (int i = 3; i >= 0; --i) {
        int my_popped_value = 0;
        ASSERT_EQ(0, my_new_stack->popObject(&my_popped_value));
    }

    ASSERT_EQ(-1, my_new_stack->numberOfElements());
}

TEST_F(MyStackTest, testPopFromEmptyStack) {
    int my_popped_value = 0;
    ASSERT_EQ(-1, my_new_stack->popObject(&my_popped_value));
}

TEST_F(MyStackTest, testNullStackElement) {
    ASSERT_EQ(-1, my_new_stack->numberOfElements());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}