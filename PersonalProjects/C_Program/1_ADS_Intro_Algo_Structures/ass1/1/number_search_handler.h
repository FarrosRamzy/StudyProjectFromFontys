#ifndef NUMBER_SEARCH_HANDLER
#define NUMBER_SEARCH_HANDLER

#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

///////////////////////////////////////////////////////////////
//<Assignment 1.1 linear search algorithm>
//(search_handler_header)
//
// Course		: SD
// Student		: Farros Ramzy (3767353)
// Date			: 13-09-2023
//
///////////////////////////////////////////////////////////////

#define MAX_SIZE_OF_ARRAY 100000
#define MAX_VAL_OF_REPEAT 100000
#define MAX_VAL_OF_INPUT 100000

int check_array_size(int);
int check_input_val(int);
void populate_array(int *, int, int);
int check_repetition_time(int);
bool find_minimum_from_repeating_val(int *, int *, int, int);

#endif