#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "number_search_handler.h"

///////////////////////////////////////////////////////////////
//<Assignment 1.1 linear search algorithm>
//(search_handler_file)
//
// Course		: SD
// Student		: Farros Ramzy (3767353)
// Date			: 13-09-2023
//
///////////////////////////////////////////////////////////////

/**
 * @brief Array size check function.
 *
 * @note This function receives the input value as the intended size of the array
 * 		 and checks if the size is correct, due to its min and max limitation.
 *
 * @param size_of_input the value of the array size.
 * @return int 0 when the input is invalid and 1 only if the input is valid.
 */
int check_array_size(int size_of_input)
{
	if (size_of_input > MAX_SIZE_OF_ARRAY || size_of_input < 1)
	{
		return 0;
	}

	return 1;
}

/**
 * @brief Input value check function.
 *
 * @note This function receives the input number for the created array and checks
 * 		 its value if it is fit with the min and max limitation.
 *
 * @param input_val The incoming numbers which will populate the array if they
 *        are valid.
 * @return int 0 when the input is invalid and 1 only if the input is valid.
 */
int check_input_val(int input_val)
{
	int return_val = 0;
	if (input_val < 0 || input_val > MAX_VAL_OF_INPUT)
	{
		return_val = 0;
	}
	else
	{
		return_val = 1;
	}
	return return_val;
}

/**
 * @brief Input array's adder.
 *
 * @note This function is responsible to populate the intended array with the
 * 		 scanned input values by their queue number.
 *
 * @param input_array The array where the input value will be placed in.
 * @param queue The position of the array where the input number will be placed.
 * @param input_val The valid input numbers which will populate the array.
 */
void populate_array(int *input_array, int queue, int input_val)
{
	(*(input_array + queue)) = input_val;
}

/**
 * @brief Repetition limit checker.
 *
 * @note This function is responsible to check if the repeat limit is within the
 *       acceptable min and max limit or not.
 *
 * @param repeat_val The repetition limit value.
 * @return int 0 when the input is invalid and 1 only if the input is valid.
 */
int check_repetition_time(int repeat_val)
{
	if (repeat_val > MAX_VAL_OF_REPEAT || repeat_val < 1)
	{
		return 0;
	}
	return 1;
}

/**
 * @brief Minimum value's finder.
 *
 * @note This function is intended to find the minimum value of the repeating
 *       numbers within the input array if the number is repeating by the exact
 * 		 same times of the repeat limit value.
 *
 * @param input_array The array of numbers.
 * @param minimum_val The minimum value from the repeating numbers.
 * @param size_of_array
 * @param repeat_val The repeat limit restriction.
 * @return true if the minimum value is found and valid within the restriction.
 * @return false if the minimum value is not found or invalid.
 */
bool find_minimum_from_repeating_val(int *input_array, int *minimum_val, int size_of_array, int repeat_val)
{
	int *repeated_nr = NULL;
	int size_of_repeated_nr = MAX_SIZE_OF_ARRAY + 1;
	repeated_nr = (int *)calloc(size_of_repeated_nr, sizeof(int));

	if (repeated_nr == NULL)
	{
		free(repeated_nr);
		return false;
	}

	for (int i = 0; i < size_of_array; i++)
	{
		(*(repeated_nr + *(input_array + i)))++;
	}

	for (int i = 0; i < MAX_VAL_OF_REPEAT; i++)
	{
		if ((*(repeated_nr + i)) == repeat_val)
		{
			*minimum_val = i;
			free(repeated_nr);
			return true;
		}
	}
}