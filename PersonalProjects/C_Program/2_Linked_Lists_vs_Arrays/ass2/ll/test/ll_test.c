/**
 * @file ll_test.c
 * @author Farros Ramzy (platform prepared by R. Frenken)
 * @brief SD Assignment 2.2 (linked-list unit-test)
 * @version 1.0
 * @date 2023-10-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <string.h>

#include "linkedlist.h"
#include "my_malloc.h"
#include "unity.h"

#define MY_RUN_TEST(func) RUN_TEST(func, 0)

// this malloc is a prototype for unit-testing.
#define malloc my_custom_malloc

void setUp(void)
{
  // This is run before EACH test
}

void tearDown(void)
{
  // This is run after EACH test
}

/**
 * @brief 1st test of add_first
 *
 * @note Function should succeed to add an item to the
 *       linked list even if the head is NULL.
 *
 */
void test_add_first_at_null(void)
{
  /*initialize return signal and value*/
  int ret;
  int val;

  /*initialize the list*/
  ITEM *list = NULL;

  ret = add_first(&list, 1); // add item
  val = list->value;         // save item value

  /*clean list:*/
  reset_counter();
  clean(&list);

  TEST_ASSERT_EQUAL(0, ret); // check if "add" success.
  TEST_ASSERT_EQUAL(1, val); // check the head value.
}

/**
 * @brief 2nd test of add_first
 *
 * @note Function should succeed to add an item in front
 *       of the head of the list as the new head if the
 *       memory is not full.
 *
 */
void test_add_first_as_new_head(void)
{
  /*initialize return signal and value*/
  int ret;
  int val;

  /*initialize the list*/
  ITEM *list = NULL;

  /*add item to list*/
  list = (ITEM *)malloc(sizeof(ITEM));
  list->next = NULL;
  list->value = 3;

  /*add new heads*/
  ret = add_first(&list, 2);
  ret = add_first(&list, 1);
  ret = add_first(&list, 0);

  val = list->value; // save item value

  /*clean list:*/
  reset_counter();
  clean(&list);

  TEST_ASSERT_EQUAL(0, ret); // check if "add" success.
  TEST_ASSERT_EQUAL(0, val); // check the head value.
}

/**
 * @brief 3rd test of add_first
 *
 * @note Function should failed to add a new head when
 *       the memory is full.
 *
 */
void test_reject_add_first_at_full_memory(void)
{
  /*initialize return signal and value*/
  int ret;
  int val;

  /*initialize the list*/
  ITEM *list = NULL;

  /*add new heads*/
  ret = add_first(&list, 4);
  ret = add_first(&list, 3);
  ret = add_first(&list, 2);
  ret = add_first(&list, 1); //---- max mem
  ret = add_first(&list, 0);

  val = list->value; // save item value

  /*clean list:*/
  reset_counter();
  clean(&list);

  TEST_ASSERT_EQUAL(-1, ret); // check if "add" failed.
  TEST_ASSERT_EQUAL(1, val);  // check the head value.
}

/**
 * @brief 1st test of add_last
 *
 * @note Function should succeed to add a new item at
 *       the tail of the linked-list. And it must add
 *       the new item as the head if the head of the
 *       linked-list is NULL.
 *
 */
void test_add_last_at_null(void)
{
  /*initialize return signal and value*/
  int ret;
  int val;

  /*initialize the list*/
  ITEM *list = NULL;

  /*add new items*/
  ret = add_last(&list, 0);

  val = list->value; // save item value

  /*clean list:*/
  reset_counter();
  clean(&list);

  TEST_ASSERT_EQUAL(0, ret); // check if "add" success.
  TEST_ASSERT_EQUAL(0, val); // check the added value.
}

/**
 * @brief 2nd test of add_last
 *
 * @note Function should succeed to add a new item at
 *       the tail of the linked-list.
 *
 */
void test_add_last_as_new_tail(void)
{
  /*initialize return signal and value*/
  int ret;
  int val;

  /*initialize the list and it's temporary*/
  ITEM *list = NULL;
  ITEM *temp = NULL;

  /*add the head of the list*/
  list = (ITEM *)malloc(sizeof(ITEM));
  list->next = NULL;
  list->value = 0;

  /*add new items*/
  ret = add_last(&list, 1);
  ret = add_last(&list, 2);

  temp = list;

  /*find last item*/
  while (temp->next != NULL)
  {
    temp = temp->next;
  }

  val = temp->value; // save item value

  /*clean list*/
  reset_counter();
  clean(&list);

  TEST_ASSERT_EQUAL(0, ret); // check if "add" success.
  TEST_ASSERT_EQUAL(2, val); // check the added value.
}

/**
 * @brief 3rd test of add_last
 *
 * @note Function should be failed to add a new item by
 *       the tail of the linked-list if the memory is
 *       full.
 *
 */
void test_reject_add_last_at_full_memory(void)
{
  /*initialize return signal and value*/
  int ret;
  int val;

  /*initialize the list and it's temporary*/
  ITEM *list = NULL;
  ITEM *temp = NULL;

  /*add new items*/
  ret = add_last(&list, 0);
  ret = add_last(&list, 1);
  ret = add_last(&list, 2);
  ret = add_last(&list, 3); //---- max mem
  ret = add_last(&list, 4);
  ret = add_last(&list, 5);

  temp = list;

  /*find last item*/
  while (temp->next != NULL)
  {
    temp = temp->next;
  }

  val = temp->value; // save item value

  /*clean list:*/
  reset_counter();
  clean(&list);

  TEST_ASSERT_EQUAL(-1, ret); // check if "add" fails.
  TEST_ASSERT_EQUAL(3, val);  // check the added value.
}

/**
 * @brief 1st test of add after
 *
 * @note Function should succeed to add a new item in
 *       the middle of the linked list, after a certain
 *       selected item if both the list and the item
 *       are available.
 *
 */
void test_add_after(void)
{
  /*initialize return signal and values*/
  int ret;
  int head_val;
  int target_val;
  int tail_val;

  /*initialize the list, c_item, and it's temporary*/
  ITEM *list = NULL;
  ITEM *c_item = NULL;
  ITEM *temp = NULL;

  /*add items*/
  ret = add_first(&list, 0);
  ret = add_last(&list, 2);

  /*select c_item pos*/
  c_item = list;

  /*add new item*/
  ret = add_after(list, c_item, 1);

  temp = list;

  head_val = temp->value; // save head value

  /*find target item*/
  while (temp != c_item)
  {
    temp = temp->next;
  }

  temp = temp->next;

  target_val = temp->value; // save selected item's value

  /*find last item*/
  while (temp->next != NULL)
  {
    temp = temp->next;
  }

  tail_val = temp->value; // save tail item's value

  reset_counter();
  clean(&list);

  TEST_ASSERT_EQUAL(0, ret); // check if "add" success.

  /*check the added values.*/
  TEST_ASSERT_EQUAL(0, head_val);
  TEST_ASSERT_EQUAL(1, target_val);
  TEST_ASSERT_EQUAL(2, tail_val);
}

/**
 * @brief 2nd test of add after
 *
 * @note Function should be failed to add a new item if
 *       the list is NULL, or the c_item is not found.
 *
 */
void test_reject_add_after_at_null_list(void)
{
  /*initialize return signal*/
  int ret;

  /*initialize the list and c_item*/
  ITEM *list = NULL;
  ITEM *c_item = NULL;

  /*add c_item*/
  c_item = (ITEM *)malloc(sizeof(ITEM));
  c_item->next = NULL;
  c_item->value = 0;

  /*add after*/
  ret = add_after(list, c_item, 1);

  /*clean list*/
  reset_counter();
  clean(&list);
  clean(&c_item);

  TEST_ASSERT_EQUAL(-1, ret); // check if "add" fails.
}

/**
 * @brief 3rd test of add_after
 *
 * @note Function must be failed when the c_item is NULL
 *       or not available.
 *
 */
void test_reject_add_after_with_unknown(void)
{
  /*initialize return signal and value*/
  int ret;
  int val;

  /*initialize the list, c_item, and it's temporary*/
  ITEM *list = NULL;
  ITEM *c_item = NULL;
  ITEM *temp = NULL;

  /*add new items*/
  ret = add_first(&list, 0);
  ret = add_after(list, c_item, 1);

  temp = list;

  /*find the item*/
  while (temp != c_item)
  {
    temp = temp->next;
    if (temp == NULL)
    {
      val = -1;
    }
    else
    {
      val = temp->value;
    }
  }

  /*clean list:*/
  reset_counter();
  clean(&list);

  TEST_ASSERT_EQUAL(-1, ret); // check if "add" fails.
  TEST_ASSERT_EQUAL(-1, val); // check if the new value is never added.
}

/**
 * @brief 1st test of rem_first
 *
 * @note Function should succeed to remove the first item
 *       if the head of linked-list is founded.
 *
 */
void test_rem_first(void)
{
  /*initialize return signal and value*/
  int ret;
  int val;

  /*initialize the list*/
  ITEM *list = NULL;

  /*add new head*/
  list = (ITEM *)malloc(sizeof(ITEM));
  list->next = NULL;
  list->value = 1;

  /*add new items*/
  ret = add_last(&list, 2);
  ret = add_first(&list, 3);
  ret = add_first(&list, 0);

  /*remove head*/
  ret = rem_first(&list);

  val = list->value; // save item value

  /*clean list:*/
  reset_counter();
  clean(&list);

  TEST_ASSERT_EQUAL(0, ret); // check if "remove" success.
  TEST_ASSERT_EQUAL(3, val); // check the new head value.
}

/**
 * @brief 2nd test of rem_first
 *
 * @note Function should be failed to remove the head of the
 *       linked-list if the head of the linked-list is not
 *       available.
 *
 */
void test_reject_rem_first_at_null_list(void)
{
  int ret;

  ITEM *list = NULL;

  ret = rem_first(&list);

  reset_counter();
  clean(&list);

  TEST_ASSERT_EQUAL(-1, ret);
}

/**
 * @brief 1st test of rem_last
 *
 * @note Function should succeed to remove the item at the
 *       tail of the linked-list if the linked-list is not
 *       empty.
 *
 */
void test_rem_last(void)
{
  int ret;
  int val;

  ITEM *list = NULL;
  ITEM *temp = NULL;

  ret = add_first(&list, 3);
  ret = add_first(&list, 2);
  ret = add_first(&list, 1);
  ret = add_first(&list, 0);

  ret = rem_last(&list);

  temp = list;

  while (temp->next != NULL)
  {
    temp = temp->next;
  }

  val = temp->value;

  reset_counter();
  clean(&list);

  TEST_ASSERT_EQUAL(0, ret);
  TEST_ASSERT_EQUAL(2, val);
}

/**
 * @brief 2nd test of rem_last
 *
 * @note Function should be failed to remove the item at the
 *       tail of the linked-list if the list is NULL.
 *
 */
void test_reject_rem_last_at_null_list(void)
{
  int ret;

  ITEM *list = NULL;

  ret = rem_last(&list);

  reset_counter();
  clean(&list);

  TEST_ASSERT_EQUAL(-1, ret);
}

/**
 * @brief 1st test of rem_after
 *
 * @note Function should succeed to remove the item after the
 *       selected item of the list without destruct the rest
 *       of the linked-list.
 *
 */
void test_rem_after(void)
{
  int ret;
  int val;

  ITEM *list = NULL;
  ITEM *c_item = NULL;

  list = (ITEM *)malloc(sizeof(ITEM));

  list->next = NULL;
  list->value = 0;

  c_item = list;

  ret = add_last(&list, 1);
  ret = add_last(&list, 3);

  c_item = c_item->next;

  ret = add_after(list, c_item, 2); // add new item

  ret = rem_after(list, c_item); // remove new item

  val = c_item->next->value;

  reset_counter();
  clean(&list);

  TEST_ASSERT_EQUAL(0, ret);
  TEST_ASSERT_EQUAL(3, val);
}

/**
 * @brief 2nd test of rem_after
 *
 * @note Function should be failed to remove the intended
 *       item if the selected item is empty or unknown.
 *
 */
void test_reject_rem_after_with_unknown(void)
{
  int ret;

  ITEM *list = NULL;
  ITEM *c_item = NULL;

  list = (ITEM *)malloc(sizeof(ITEM));
  list->next = NULL;
  list->value = 0;

  ret = add_last(&list, 1);
  ret = add_last(&list, 2);
  ret = add_last(&list, 3);

  ret = rem_after(list, c_item);

  reset_counter();
  clean(&list);

  TEST_ASSERT_EQUAL(-1, ret);
}

int main(int argc, char *argv[])
{
  UnityBegin();

  /* Put your UTs here */
  MY_RUN_TEST(test_add_first_at_null);
  MY_RUN_TEST(test_add_first_as_new_head);
  MY_RUN_TEST(test_reject_add_first_at_full_memory);

  MY_RUN_TEST(test_add_last_at_null);
  MY_RUN_TEST(test_add_last_as_new_tail);
  MY_RUN_TEST(test_reject_add_last_at_full_memory);

  MY_RUN_TEST(test_add_after);
  MY_RUN_TEST(test_reject_add_after_at_null_list);
  MY_RUN_TEST(test_reject_add_after_with_unknown);

  MY_RUN_TEST(test_rem_first);
  MY_RUN_TEST(test_reject_rem_first_at_null_list);

  MY_RUN_TEST(test_rem_last);
  MY_RUN_TEST(test_reject_rem_last_at_null_list);

  MY_RUN_TEST(test_rem_after);
  MY_RUN_TEST(test_reject_rem_after_with_unknown);

  return UnityEnd();
}
