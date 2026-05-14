/**
 * @file my_malloc.c
 * @author Farros Ramzy
 * @brief This c file is containing the custom malloc function
 *        to limit the allocation process, which is needed for
 *        a full memory unit-testing.
 * @version 0.1
 * @date 2023-10-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "my_malloc.h"

/*static counter to limit the allocation size (only for size testing).*/
static int allocation_count = 0;
static int max_allocations = 4; // this value needed for testing

/**
 * @brief A custom malloc to limit the allocation.
 *
 * @param size the size of the memory needed for a memory allocation.
 * @return void*
 */
void *my_custom_malloc(size_t size)
{

    if (allocation_count >= max_allocations)
    {
        return NULL; // Simulate a memory allocation failure
    }
    else
    {
        allocation_count++;
    }
    return (malloc(size)); // Use the real malloc for other allocations
}

/**
 * @brief A reset function to reset the allocation counter
 *
 */
void reset_counter()
{
    allocation_count = 0;
}
