#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include "mystack.h"
#include "myqueue.h"

QueueMeta_t *myqueue_create(int item_size)
{
	QueueMeta_t *new_queue = (QueueMeta_t *)malloc(sizeof(QueueMeta_t));
	if (new_queue != NULL)
	{
		new_queue->stack_in = mystack_create(item_size);
		if (new_queue->stack_in == NULL)
		{
			free(new_queue);
			return NULL;
		}

		new_queue->stack_out = mystack_create(item_size);
		if (new_queue->stack_out == NULL)
		{
			mystack_destroy(&(new_queue->stack_in));
			free(new_queue);
			return NULL;
		}

		new_queue->item_size = item_size;
	}
	return new_queue;
}

void myqueue_delete(QueueMeta_t **queue)
{
	if (*queue != NULL)
	{
		if ((*queue)->stack_in != NULL)
		{
			mystack_destroy(&((*queue)->stack_in));
		}

		if ((*queue)->stack_out != NULL)
		{
			mystack_destroy(&((*queue)->stack_out));
		}

		free(*queue);
		*queue = NULL;
	}
}

int myqueue_enqueue(QueueMeta_t *que, void *obj)
{
	int push_to_que = 0;

	if (que == NULL || obj == NULL)
	{
		push_to_que = -1;
	}
	else
	{
		push_to_que = mystack_push(que->stack_in, obj);
	}

	return push_to_que;
}

int myqueue_dequeue(QueueMeta_t *queue, void *obj)
{
	int mystack_out_element = 0;
	int mystack_in_element = 0;
	int mystack_pop_status = 0;
	int mystack_push_status = 0;

	void *my_temp_obj = NULL; // Initialize to NULL

	if (queue == NULL || obj == NULL)
	{
		return -1; // Invalid arguments
	}

	mystack_out_element = mystack_nofelem(queue->stack_out);

	if (mystack_out_element == 0)
	{
		mystack_in_element = mystack_nofelem(queue->stack_in);
		my_temp_obj = malloc(queue->item_size);
		while (mystack_in_element > 0)
		{
			if (my_temp_obj == NULL)
			{
				// Clean up and return on memory allocation failure
				free(my_temp_obj);
				return -1;
			}

			mystack_pop_status = mystack_pop(queue->stack_in, my_temp_obj);
			if (mystack_pop_status == 0)
			{
				mystack_push_status = mystack_push(queue->stack_out, my_temp_obj);
				if (mystack_push_status != 0)
				{
					// Clean up and return on failure
					free(my_temp_obj);
					return -1;
				}
			}
			else
			{
				// Clean up and return on failure
				free(my_temp_obj);
				return -1;
			}

			mystack_in_element = mystack_nofelem(queue->stack_in);
		}
	}

	if (mystack_pop_status == 0)
	{
		mystack_pop_status = mystack_pop(queue->stack_out, obj);
		if (mystack_pop_status != 0)
		{
			// Clean up and return on failure
			free(my_temp_obj);
			return -1;
		}
	}

	// Free the temporary object after it has been used
	free(my_temp_obj);

	return 0;
}
