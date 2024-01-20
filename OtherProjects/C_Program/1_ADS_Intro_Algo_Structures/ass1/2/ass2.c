#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include "number_sort_handler.h"

/* 2nd part of Assignment 1 SD */

///////////////////////////////////////////////////////////////
//<Assignment 1.2 sorting algorithm>
//
// Course		: SD
// Student		: Farros Ramzy (3767353)
// Date			: 15-09-2023
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
	int *array_of_numbers = NULL;
	int size_of_array = 0;

	/*Initializing the input and output values:*/
	int input_val = 0;
	int outcome = 0;

	/*Initializing the size of the SUM:*/
	int size_of_sum = 0;

	//Reading the incoming input size value.
	scanf("%d", &size_of_array);

	// Checking if the input size valid or not.
	if (check_size_of_list(size_of_array) == 0)
	{
		printf("ERROR: size of the list is invalid!\n");
		exit(EXIT_FAILURE);
	}

	/*Allocates the initialized array by the size value using the contiguous
	allocation.*/
	array_of_numbers = (int *)calloc(size_of_array, sizeof(int));

	// Checks if the array is available or not.
	if (array_of_numbers == NULL)
	{
		printf("ERROR: Array setup has failed!\n");
		free(array_of_numbers);
		exit(EXIT_FAILURE);
	}

	// Scans and adds input to the N array only if the input values are valid.
	for (int i = 0; i < size_of_array; i++)
	{
		scanf("%d", &input_val);
		if (check_input_val(input_val) == 0)
		{
			printf("ERROR: Input value is invalid!\n");
			free(array_of_numbers);
			exit(EXIT_FAILURE);
		}
		else
		{
			add_input_to_array(array_of_numbers, i, input_val);
		}
	}

	// Scans the limit value of the SUM (K).
	scanf("%d", &size_of_sum);

	//Checks if the limit of the SUM numbers is valid or not.
	if (check_size_of_sum(size_of_sum) == 0)
	{
		printf("ERROR: SUM size is invalid!\n");
		free(array_of_numbers);
		exit(EXIT_FAILURE);
	}

	//Sorting the input array by min to max order.
	sort_array_elements(array_of_numbers, size_of_array);


	/* implement her your code e.g. like this
	 * outcome = get_difference_between_min_and_max_sum_of_k_elems( choose your own arguments );
	 */

	//Catches the min and max SUM values and return the difference between them.
	outcome = get_difference_val_of_min_max(array_of_numbers, size_of_array, size_of_sum);

	//Remove the array to free the used memory.
	free(array_of_numbers);

	/* this is the (performance) test code, please don't touch it */

	t = clock() - t;
	time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("difference between minimum and maximum sum of K elements is %d\n", outcome);
#ifdef TEST_TIME
	printf("time needed was %f seconds\n", time_taken);
#endif
	return 0;
}
