#ifndef NUMBER_SORT_HANDLER_H
#define NUMBER_SORT_HANDLER_H

#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////
//<Assignment 1.2 sorting algorithm>
//(sorting_handler_header)
//
// Course		: SD
// Student		: Farros Ramzy (3767353)
// Date			: 15-09-2023
//
///////////////////////////////////////////////////////////////

#define MAX_SIZE_OF_ARRAY 999
#define MIN_SIZE_OF_ARRAY 1
#define MAX_SIZE_OF_SUM 998
#define MIN_SIZE_OF_SUM 1
#define MAX_INPUT_VAL 9999
#define MIN_INPUT_VAL 0

int check_size_of_list(int);
int check_input_val(int);
void add_input_to_array(int *, int, int);
int check_size_of_sum(int);
void sort_array_elements(int *, int);
int get_difference_val_of_min_max(int *, int, int);

#endif