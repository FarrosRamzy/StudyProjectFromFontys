#include <string.h>
#include <stdio.h>

#include "mystack.h"
#include "unity.h"
#include "testrunner.h"

/* I rather dislike keeping line numbers updated,
so I made my own macro to ditch the line number*/
#define MY_RUN_TEST(func) RUN_TEST(func, 0)


void setUp(void)
{

}

void tearDown(void)
{
    // This is run after EACH test
}

void test_mystack_create(void)
{
	StackMeta_t *my_new_stack = mystack_create(sizeof(int));

	TEST_ASSERT_NOT_NULL(my_new_stack);
	TEST_ASSERT_NULL(my_new_stack->stack);
	TEST_ASSERT_EQUAL(sizeof(int), my_new_stack->objsize);
	TEST_ASSERT_EQUAL(0,my_new_stack->numelem);

	free(my_new_stack);
}

void test_mystack_push(void)
{
	StackMeta_t *my_new_stack = mystack_create(sizeof(int));

	int my_data = 86;
	int my_push_result = mystack_push(my_new_stack, &my_data);

	TEST_ASSERT_EQUAL(0,my_push_result);
	TEST_ASSERT_NOT_NULL(my_new_stack->stack);
	TEST_ASSERT_EQUAL(1, my_new_stack->numelem);

	mystack_destroy(&my_new_stack);
}

void test_mystack_push_to_null(void)
{
    int my_data = 86;
	int my_push_result = mystack_push(NULL, &my_data);

    TEST_ASSERT_EQUAL(-1, my_push_result);
}

void test_mystack_push_a_null_object(void)
{
    StackMeta_t *my_new_stack = mystack_create(sizeof(int));

	int my_push_result = mystack_push(my_new_stack, NULL);

    TEST_ASSERT_EQUAL(-1, my_push_result);
    
	mystack_destroy(&my_new_stack);
}

void test_mystack_pop(void)
{
    StackMeta_t *my_new_stack = mystack_create(sizeof(int));

    int my_data = 86;
	int my_push_result = mystack_push(my_new_stack, &my_data);

    TEST_ASSERT_EQUAL(0, my_push_result);

    int popped_data = 0;
	int my_pop_result = mystack_pop(my_new_stack, &popped_data);

	int num_of_element = mystack_nofelem(my_new_stack);

    TEST_ASSERT_EQUAL(0, my_pop_result);
    TEST_ASSERT_EQUAL(my_data, popped_data);
    TEST_ASSERT_EQUAL(0, num_of_element);

    mystack_destroy(&my_new_stack);
}

void test_mystack_pop_a_null_stack(void)
{
    int popped_value = 0;
	int my_pop_result = mystack_pop(NULL, &popped_value);

    TEST_ASSERT_EQUAL(-1, my_pop_result);
    TEST_ASSERT_EQUAL(0, popped_value);
}

void test_mystack_pop_an_empty_stack(void)
{
    StackMeta_t *my_new_stack = mystack_create(sizeof(int));

    int popped_value = 0;
	int my_pop_result = mystack_pop(my_new_stack, &popped_value);

    TEST_ASSERT_EQUAL(-1, my_pop_result);
    
	mystack_destroy(&my_new_stack);
}

void test_mystack_pop_invalid_object(void)
{
    StackMeta_t *stack = mystack_create(sizeof(int));
    int value = 42;

	int my_push_result = mystack_push(stack, &value);
	int my_pop_result = mystack_pop(stack, NULL);

    TEST_ASSERT_EQUAL(0, my_push_result);
    TEST_ASSERT_EQUAL(-1, my_pop_result);

    mystack_destroy(&stack);
}

void test_mystack_destroy(void)
{
    StackMeta_t *my_new_stack = NULL;
	my_new_stack = mystack_create(sizeof(int));
    
	mystack_destroy(&my_new_stack);

    TEST_ASSERT_NULL(my_new_stack);
}

void test_mystack_destroy_invalid_stack(void)
{
	StackMeta_t *my_new_stack = NULL;
    mystack_destroy(&my_new_stack);

    TEST_ASSERT_NULL(my_new_stack);
}

int main (int argc, char * argv[]) {
	UnityBegin();

	MY_RUN_TEST(test_mystack_create);

	MY_RUN_TEST(test_mystack_push);
	MY_RUN_TEST(test_mystack_push_to_null);
	MY_RUN_TEST(test_mystack_push_a_null_object);

	MY_RUN_TEST(test_mystack_pop);
	MY_RUN_TEST(test_mystack_pop_a_null_stack);
	MY_RUN_TEST(test_mystack_pop_an_empty_stack);
	MY_RUN_TEST(test_mystack_pop_invalid_object);

	MY_RUN_TEST(test_mystack_destroy);
	MY_RUN_TEST(test_mystack_destroy_invalid_stack);

	return UnityEnd();
}
