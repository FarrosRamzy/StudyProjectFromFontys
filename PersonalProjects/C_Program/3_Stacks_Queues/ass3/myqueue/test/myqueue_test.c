#include <string.h>
#include <stdio.h>
#include "mystack.h"
#include "myqueue.h"
#include "unity.h"
#include "testrunner.h"

/*rather dislike keeping line numbers updated,
so I made my own macro to ditch the line number*/
#define MY_RUN_TEST(func) RUN_TEST(func, 0)

void setUp(void)
{
}

void tearDown(void)
{
    // This is run after EACH test
}

void test_queue_create(void)
{
	int size_of_queue = 7;
	QueueMeta_t *my_new_queue = myqueue_create(size_of_queue);

	TEST_ASSERT_NOT_NULL(my_new_queue);
	TEST_ASSERT_NOT_NULL(my_new_queue->stack_in);
	TEST_ASSERT_NOT_NULL(my_new_queue->stack_out);
	TEST_ASSERT_EQUAL_INT(7,my_new_queue->item_size);

	myqueue_delete(&my_new_queue);
}

void test_queue_create_delete(void)
{
	int size_of_queue = 7;
	QueueMeta_t *my_new_queue = NULL;
	my_new_queue = myqueue_create(size_of_queue);
	
	TEST_ASSERT_NOT_NULL(my_new_queue);

	myqueue_delete(&my_new_queue);

	TEST_ASSERT_NULL(my_new_queue);
}

void test_enqueue(void)
{
	QueueMeta_t *my_new_queue = myqueue_create(sizeof(int));
	
	TEST_ASSERT_NOT_NULL(my_new_queue);

	int element = 30;

	int enqueue_result = myqueue_enqueue(my_new_queue, &element);
	
	TEST_ASSERT_EQUAL_INT(0, enqueue_result);

	myqueue_delete(&my_new_queue);
}

void test_enqueue_where_queue_is_null(void)
{
    QueueMeta_t *my_new_queue = NULL;

    int element = 30;

    int enqueue_result = myqueue_enqueue(my_new_queue, &element);
    
	TEST_ASSERT_EQUAL_INT(-1, enqueue_result);

    // Clean up the queue
    myqueue_delete(&my_new_queue);
}

void test_enqueue_where_element_is_null(void)
{
    QueueMeta_t *my_new_queue = myqueue_create(sizeof(int));
    
	TEST_ASSERT_NOT_NULL(my_new_queue);

    int enqueue_result = myqueue_enqueue(my_new_queue, NULL);
    
	TEST_ASSERT_EQUAL_INT(-1, enqueue_result);

    // Clean up the queue
    myqueue_delete(&my_new_queue);
}

void test_dequeue(void)
{
	// Create a queue for testing
    QueueMeta_t *my_new_queue = myqueue_create(sizeof(int));
    TEST_ASSERT_NOT_NULL(my_new_queue);

    int elements[] = {1, 2, 3};
	int enqueue_result;
    int dequeue_result;
    int dequeued_element;

    // Enqueue data into the queue for testing
    for (int i = 0; i < sizeof(elements) / sizeof(elements[0]); ++i)
    {
        enqueue_result = myqueue_enqueue(my_new_queue, &elements[i]);

        TEST_ASSERT_EQUAL_INT(0, enqueue_result);
    }

    // Test dequeue with valid arguments
    dequeue_result = myqueue_dequeue(my_new_queue, &dequeued_element);

    TEST_ASSERT_EQUAL_INT(0, dequeue_result);
    TEST_ASSERT_EQUAL_INT(elements[0], dequeued_element);

	myqueue_delete(&my_new_queue);
}

void test_dequeue_when_queue_is_null(void)
{
	QueueMeta_t *my_new_queue = NULL;
	int dequeue_result;
	int dequeued_element;

	dequeue_result = myqueue_dequeue(my_new_queue, &dequeued_element);
    TEST_ASSERT_EQUAL_INT(-1, dequeue_result);
}

void test_dequeue_when_element_is_null(void)
{
	QueueMeta_t *my_new_queue = NULL;
	my_new_queue = myqueue_create(sizeof(int));

	int dequeue_result;

	dequeue_result = myqueue_dequeue(my_new_queue, NULL);
    
	TEST_ASSERT_EQUAL_INT(-1, dequeue_result);
	myqueue_delete(&my_new_queue);
}

int main () {
	UnityBegin();
	MY_RUN_TEST(test_queue_create);
	MY_RUN_TEST(test_queue_create_delete);

	MY_RUN_TEST(test_enqueue);
	MY_RUN_TEST(test_enqueue_where_queue_is_null);
	MY_RUN_TEST(test_enqueue_where_element_is_null);
	
	MY_RUN_TEST(test_dequeue);
	MY_RUN_TEST(test_dequeue_when_queue_is_null);
	MY_RUN_TEST(test_dequeue_when_element_is_null);
	return UnityEnd();
}
