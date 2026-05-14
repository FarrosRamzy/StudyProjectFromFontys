#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "number_search_handler.h"

/* 1st part of Assignment 1 SD */

///////////////////////////////////////////////////////////////
//<Assignment 1.1 linear search algorithm>
//
// Course		: SD
// Student		: Farros Ramzy (3767353)
// Date			: 13-09-2023
//
///////////////////////////////////////////////////////////////

int main()
{
	/* this is code to measure the time of your algorithm, please don't touch it */

	clock_t t;
	double time_taken;

	t = clock();

	/* read here the stdin to get the values of N, a1...an and K
	 * and store them
	 *
	 * for this you can use scanf e.g. like this:
	 *
	 * int n;
	 * scanf("%d", &n);
	 */

	/*Initializing an array to capture the N inputs:*/
	int *array_of_nr = NULL;
	int size_of_arr = 0;

	/*Initializing the limitation of repeat numbers.*/
	int repeat_lim = 0;

	/*Initializing the input and output values.*/
	int input_val = 0;
	int outcome = 0;

	/*Initializing the minimum value.*/
	bool minimum_has_found = false;
	int minimum_val = 0;

	// Reading the incoming input size value.
	scanf("%d", &size_of_arr);

	// Checking if the input size valid or not.
	if (check_array_size(size_of_arr) == 0)
	{
		printf("ERROR: input size is invalid!\n");
		exit(EXIT_FAILURE);
	}

	/*Allocates the initialized array by the size value using the contiguous
	allocation.*/
	array_of_nr = (int *)calloc(size_of_arr, sizeof(int));

	// Checks if the array is available or not.
	if (array_of_nr == NULL)
	{
		printf("ERROR: Array setup has failed!\n");
		free(array_of_nr);
		exit(EXIT_FAILURE);
	}

	// Scans and adds input to the N array only if the input values are valid.
	for (int i = 0; i < size_of_arr; i++)
	{
		scanf("%d", &input_val);
		if (check_input_val(input_val) == 1)
		{
			populate_array(array_of_nr, i, input_val);
		}
		else
		{
			printf("ERROR: Input value is invalid!\n");
			free(array_of_nr);
			exit(EXIT_FAILURE);
		}
	}

	// Scans the limit value of reapeating numbers (K).
	scanf("%d", &repeat_lim);
	
	//Checks if the limit value of the repeating numbers is valid or not.
	if (check_repetition_time(repeat_lim) == 0)
	{
		printf("ERROR: repeat value is invalid!\n");
		free(array_of_nr);
		exit(EXIT_FAILURE);
	}

	// Searches the minimum value with the correct repeats limit within the array.
	minimum_has_found = find_minimum_from_repeating_val(array_of_nr, &minimum_val, size_of_arr, repeat_lim);

	// Checks if the minimum value has founded or not.
	if (minimum_has_found == false)
	{
		printf("ERROR: minimum value is invalid!\n");
		free(array_of_nr);
		exit(EXIT_FAILURE);
	}

	/* implement her your code e.g. like this
	 * outcome = get_minimum_number_with_k_occurences( choose your own arguments );
	 */

	outcome = minimum_val;

	// Remove the array to free the used memory.
	free(array_of_nr);

	/* this is the (performance) test code, please don't touch it */

	t = clock() - t;
	time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("minimum number of K occurences is %d\n", outcome);
#ifdef TEST_TIME
	printf("time needed was %f seconds\n", time_taken);
#endif
	return 0;
}