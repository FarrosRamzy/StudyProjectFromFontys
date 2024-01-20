/**
 * @file my_malloc.h
 * @author Farros Ramzy
 * @brief This header is created for the custom malloc, for a unit testing.
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef MY_MALLOC_H
#define MY_MALLOC_H

#include <stdlib.h>

void *my_custom_malloc(size_t);
void reset_counter();

#endif