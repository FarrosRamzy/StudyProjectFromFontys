/* SD exercise 1: simple linked list API */
/* Author : R. Frenken                   */
/* Version : 1.0			 			 */

/**
 * @file linkedlist.c
 * @author Farros Ramzy (Edited from R. Frenken)
 * @brief SD Assignment 2.1 (linked-list functions)
 * @version 2.0
 * @date 2023-09-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "linkedlist.h"
#include "my_malloc.h"

// this malloc is a prototype for unit-testing.
#define malloc my_custom_malloc
/***************************************************/
/* If *list == NULL, a new list should be created, */
/* otherwise prepend a new ITEM with value value   */
/* to the existing list                            */
/* Returns -1 if not enough memory, otherwise 0    */
/***************************************************/

int add_first(ITEM **list, int value)
{
	/* Implement */
	ITEM *new_item = NULL;

	new_item = (ITEM *)malloc(sizeof(ITEM));

	// check memory availability.
	if (new_item == NULL)
	{
		return -1;
	}

	// memory is available, fill in new data.
	new_item->value = value;

	if ((*list) != NULL)
	{
		new_item->next = *list;
	}
	else
	{
		new_item->next = NULL;
	}

	(*list) = new_item;
	new_item = NULL;
	free(new_item);
	return 0;
}

/***************************************************/
/* If *list == NULL, a new list should be created, */
/* otherwise append a new ITEM with value value to */
/* the existing list                               */
/* Returns -1 if not enough memory, otherwise 0    */
/***************************************************/

int add_last(ITEM **list, int value)
{
	/* Implement */
	ITEM *new_item = NULL;
	ITEM *temporary_item = *list;

	new_item = (ITEM *)malloc(sizeof(ITEM));

	// check memory availability.
	if (new_item == NULL)
	{
		return -1;
	}

	// memory is available, fill in new data.
	new_item->value = value;
	new_item->next = NULL;

	if (temporary_item != NULL)
	{
		while (temporary_item->next != NULL)
		{
			temporary_item = temporary_item->next;
		}

		temporary_item->next = new_item;
	}
	else
	{
		(*list) = new_item;
	}

	new_item = NULL;
	free(new_item);
	return 0;
}

/****************************************************/
/* Insert a new item after current item c_item      */
/* Returns -1 if not enough memory, c_item == NULL, */
/* *list == NULL or c_item not found, otherwise 0   */
/****************************************************/

int add_after(ITEM *list, ITEM *c_item, int value)
{
	/* Implement */
	// declare
	ITEM *new_item = NULL;
	ITEM *temporary_item = list;

	// check head.
	if (temporary_item == NULL)
	{
		return -1;
	}

	// check selected item.
	if (c_item == NULL)
	{
		return -1;
	}

	// find selected item position.
	while (temporary_item != c_item)
	{
		temporary_item = temporary_item->next;

		if (temporary_item == NULL)
		{
			return -1;
		}
	}

	new_item = (ITEM *)malloc(sizeof(ITEM));

	// check memory availability.
	if (new_item == NULL)
	{
		return -1;
	}

	// fill in new_item when all the above correct.
	new_item->value = value;
	new_item->next = NULL;

	if ((temporary_item->next) != NULL)
	{
		new_item->next = temporary_item->next;
	}

	temporary_item->next = new_item;

	new_item = NULL;
	free(new_item);
	return 0;
}

/***************************************************/
/* Remove first item of the list                   */
/* Returns -1 if list==NULL, otherwise 0           */
/***************************************************/

int rem_first(ITEM **list)
{
	/* Implement */
	ITEM *first_item = NULL;

	// check if the head is not empty.
	if (*list == NULL)
	{
		return -1;
	}

	first_item = *list;
	*list = (*list)->next;
	free(first_item);
	return 0;
}

/***************************************************/
/* Remove last item of the list                    */
/* Returns -1 if list==NULL, otherwise 0           */
/***************************************************/

int rem_last(ITEM **list)
{
	ITEM *temp = NULL;
	ITEM *l_item = NULL;

	/* Implement */
	if (*list == NULL)
	{
		return -1;
	}

	temp = *list;

	// looking for the tail of the linked-list.
	while (temp->next != NULL)
	{
		l_item = temp;
		temp = temp->next;
	}

	l_item->next = NULL;
	free(temp);
	return 0;
}

/***************************************************/
/* Remove item after c_item of the list            */
/* Returns -1 list==NULL, c_item not found or      */
/* c_item is the last_element                      */
/***************************************************/

int rem_after(ITEM *list, ITEM *c_item)
{
	/* Implement */
	ITEM *temporary_item = NULL;
	ITEM *the_item = NULL;

	if (list == NULL)
	{
		return -1;
	}

	temporary_item = list;

	// searching for the c_item location
	while (temporary_item != c_item)
	{
		temporary_item = temporary_item->next;

		if (temporary_item == NULL)
		{
			return -1;
		}
	}

	// selecting the item after the c_item
	if ((temporary_item->next) == NULL)
	{
		return -1;
	}

	the_item = temporary_item->next;

	// delete the item after the c_item
	temporary_item->next = the_item->next;

	free(the_item);
	return 0;
}

/*********************************************************/
/* All dynamic memory allocated to the list is freed     */
/* Empty list should point to NULL                       */
/*********************************************************/

void clean(ITEM **list)
{
	/* Implement */
	ITEM *current_item = NULL;

	while (*list != NULL)
	{
		current_item = *list;
		*list = (*list)->next;
		free(current_item);
	}

	return;
}
