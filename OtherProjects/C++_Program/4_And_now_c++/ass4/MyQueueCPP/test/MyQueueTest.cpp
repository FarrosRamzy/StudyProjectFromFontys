#include "MyQueue.hpp"
#include <gtest/gtest.h>

class MyQueueTest : public ::testing::Test
{
protected:
    MyQueue *my_new_queue;

    void SetUp() override
    {
        my_new_queue = new MyQueue(sizeof(int));
    }

    void TearDown() override
    {
        delete my_new_queue;
    }
};

TEST_F(MyQueueTest, testEnqueue) {
    int my_value = 1;
    ASSERT_EQ(0, my_new_queue->enqueue(&my_value));
}

TEST_F(MyQueueTest, testEnqueueNullObject) {
    ASSERT_EQ(-1, my_new_queue->enqueue(nullptr));
}

TEST_F(MyQueueTest, testDequeue) {
    int my_value = 4;
    ASSERT_EQ(0, my_new_queue->enqueue(&my_value));

    int my_dequeued_value = 0;
    ASSERT_EQ(0, my_new_queue->dequeue(&my_dequeued_value));
    ASSERT_EQ(0, my_dequeued_value);
}

TEST_F(MyQueueTest, testDequeueNullObject) {
    ASSERT_EQ(-1, my_new_queue->dequeue(nullptr));
}

TEST_F(MyQueueTest, testDequeueFromEmptyQueue) {
    int my_dequeued_value = 0;
    ASSERT_EQ(0, my_new_queue->dequeue(&my_dequeued_value));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}