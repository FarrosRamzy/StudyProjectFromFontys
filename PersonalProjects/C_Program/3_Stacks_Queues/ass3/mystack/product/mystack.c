
#include "mystack.h"
#include "logging.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
/* The stack is an abstract data type.
 * this means that the internal structures are
 * never exposed to the users of the library.
 */

/* Note: the stacks have no knowledge of what types
 * they are storing. This is not a concern of the stack
 */


StackMeta_t *mystack_create(size_t objsize)
{
	StackMeta_t *new_stack = (StackMeta_t *)malloc(sizeof(StackMeta_t));
	if (new_stack != NULL)
	{
		new_stack->stack = NULL;
		new_stack->objsize = objsize;
		new_stack->numelem = 0;
	}
	return new_stack;
}

int mystack_push(StackMeta_t *stack, void *obj)
{
	StackObject_t *new_element = NULL;

	if (stack == NULL)
	{
		return -1;
	}

	if (obj == NULL)
	{
		return -1;
	}

	new_element = (StackObject_t *)malloc(sizeof(StackObject_t));

	if (new_element == NULL)
	{
		return -1;
	}

	new_element->obj = (void **)malloc(stack->objsize);

	if (new_element->obj == NULL)
	{
		free(new_element);
		return -1;
	}

	memcpy(new_element->obj, obj, stack->objsize);

	new_element->next = stack->stack;
	stack->stack = new_element;

	stack->numelem++;
	return 0;
}

int mystack_pop(StackMeta_t *stack, void *obj)
{
	StackObject_t *temp_stack = NULL;
	StackObject_t *prev_stack = NULL;

	if (stack == NULL)
	{
		return -1;
	}

	if (stack->stack == NULL)
	{
		return -1;
	}

	if (obj == NULL)
	{
		return -1;
	}

	temp_stack = stack->stack;

	while (temp_stack->next != NULL)
	{
		prev_stack = temp_stack;
		temp_stack = temp_stack->next;
	}

	if (prev_stack != NULL)
	{
		prev_stack->next = NULL;
	}
	else
	{
		stack->stack = NULL;
	}
	
	memcpy(obj, temp_stack->obj, stack->objsize);

	free(temp_stack->obj);

	free(temp_stack);

	stack->numelem--;

	return 0;
}

void mystack_destroy(StackMeta_t **stack)
{
	if (*stack != NULL)
	{
		StackObject_t *temp_stack = (*stack)->stack;
		StackObject_t *next_stack = NULL;

		while (temp_stack != NULL)
		{
			next_stack = temp_stack->next;
			free(temp_stack->obj);
			free(temp_stack);
			temp_stack = next_stack;
		}

		free(*stack);
		*stack = NULL;
	}
}

int mystack_nofelem(StackMeta_t *stack)
{
	if (stack == NULL)
	{
		return -1;
	}
	return stack->numelem;
}
