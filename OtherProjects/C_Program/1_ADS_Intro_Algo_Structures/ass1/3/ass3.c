#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

/* 3rd part of Assignment 1 SD */

///////////////////////////////////////////////////////////////
//<Assignment 1.3 sorting algorithm research>
//
// Course		: SD
// Student		: Farros Ramzy (3767353)
// Date			: 16-09-2023
//
///////////////////////////////////////////////////////////////

/**
 * @brief Swap function.
 *
 * @note This function is responsible to swap the two numbers that is intended to be swapped
 * 		 within an array.
 *
 * @param i The current value that need to be swapped.
 * @param j The next value that will be swapped with.
 */
static void swap_val(int *i, int *j)
{
	int temporary = 0;
	temporary = *i;
	*i = *j;
	*j = temporary;
}

/**
 * @brief Heapify function.
 *
 * @note The function that responsible to heap the array elements so it can sort each value by
 *       using their root elements, then looking at the largest value, and move it to the end
 *       position of the array in a recursive way.
 *
 * @param arr input array
 * @param n size of array
 * @param i element value to move.
 */
static void heapivy_val(int *arr, int n, int i)
{
	int max_val = i;
	int left_val = 2 * i + 1;
	int right_val = 2 * i + 2;

	if (left_val < n && (*(arr + left_val)) > (*(arr + max_val)))
	{
		max_val = left_val;
	}
	if (right_val < n && (*(arr + right_val)) > (*(arr + max_val)))
	{
		max_val = right_val;
	}
	if (max_val != i)
	{
		swap_val(&(*(arr + i)), &(*(arr + max_val)));
		heapivy_val(arr, n, max_val);
	}
}

/**
 * @brief Bubble sorting.
 *
 * @note This sorting algorithm is using the bubble sorting where it switches between numbers
 * 		 within the row of an array by looking at the smallest number, then repeatedly compares
 * 		 it in order with the other elements to the larger number.
 *
 * @param arr input array
 * @param n array size
 */
static void alg1(int *arr, int n)
{
	/* Here comes your implemenation of the first sorting algorithm */
	int temp = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if ((*(arr + i)) > (*(arr + j)))
			{
				temp = *(arr + i);
				(*(arr + i)) = *(arr + j);
				(*(arr + j)) = temp;
			}
		}
	}
}

/**
 * @brief Heap sort algorithm.
 * 
 * @note This sorting algorithm is using the heapify sort algorithm where the sorting is
 *       prioritize the performance by doing a consistent sorting. The function is starting by
 * 		 looking the highest heap from the array using the root of the max heap, then continuing
 * 		 down, per-steps, until all elements have been extracted.
 *
 * @param arr input array
 * @param n size of array
 */
static void alg2(int *arr, int n)
{
	/* Here comes your implementation of the second sorting algorithm */
	
	// create the maximum heap
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heapivy_val(arr, n, i);
	}
	/* sorting the number using swap and heap the value again to get the highest element of 
	   the root.*/
	for (int i = n - 1; i >= 0; i--)
	{
		swap_val(&(*arr), &(*(arr + i)));
		heapivy_val(arr, i, 0);
	}
}

/**
 * @brief Counting sort.
 * 
 * @note This sorting algorithm is using the counting sort algorithm which will look at the
 * 		 range of the array (array size), then counting the occurences per-each array elements
 * 		 by using a new counting array and the highest element number, then repeat these process
 * 		 to sorts the input numbers per-order.
 *
 * @param arr input array
 * @param n array size
 */
static void alg3(int *arr, int n)
{
	/* Here comes your implemenation of the third sorting algorithm */

	int *sorted_arr = NULL;
	int *counter_arr = NULL;
	int max_element = *arr;
	int max_constraint = 10000;

	sorted_arr = (int *)calloc(max_constraint, sizeof(int));
	counter_arr = (int *)calloc(max_constraint, sizeof(int));

	if (sorted_arr != NULL && counter_arr != NULL)
	{
		// find the largest element of the array.
		for (int i = 1; i < n; i++)
		{
			if ((*(arr + i)) > max_element)
			{
				max_element = *(arr + i);
			}
		}

		// initiate all counter elements with value 0
		for (int i = 0; i <= max_element; ++i)
		{
			(*(counter_arr + i)) = 0;
		}

		// store the array input to the counter array
		for (int i = 0; i < n; i++)
		{
			(*(counter_arr + (*(arr + i))))++;
		}

		// store the cumulative count value of each array.
		for (int i = 1; i <= max_element; i++)
		{
			(*(counter_arr + i)) += (*(counter_arr + (i - 1)));
		}

		// collecting all elements based on the index of counter array and sorting them all to the sorted array.
		for (int i = n - 1; i >= 0; i--)
		{
			(*(sorted_arr + (*(counter_arr + (*(arr + i))) - 1))) = (*(arr + i));
			(*(counter_arr + (*(arr + i))))--;
		}

		// copy the sorted array to the original array
		for (size_t i = 0; i < n; i++)
		{
			(*(arr + i)) = *(sorted_arr + i);
		}
	}

	free(sorted_arr);
	free(counter_arr);
}

/*These down below are already built in from the assignment!*/
static void read_in_arrays_to_sort(int *arr1, int *arr2, int *arr3, int n1, int n2, int n3)
{
	for (int i = 0; i < n1; i++)
	{
		scanf("%d", &arr1[i]);
	}
	for (int i = 0; i < n2; i++)
	{
		scanf("%d", &arr2[i]);
	}
	for (int i = 0; i < n3; i++)
	{
		scanf("%d", &arr3[i]);
	}
}

static void write_to_file(int *arr1, int *arr2, int *arr3, int n1, int n2, int n3, char *filename)
{
	FILE *f = fopen(filename, "w");
	if (f == NULL)
	{
		printf("Error in creating output file %s", filename);
		return;
	}
	for (int i = 0; i < n1; i++)
	{
		fprintf(f, "%d ", arr1[i]);
	};
	fprintf(f, "\n");
	for (int i = 0; i < n2; i++)
	{
		fprintf(f, "%d ", arr2[i]);
	}
	fprintf(f, "\n");
	for (int i = 0; i < n3; i++)
	{
		fprintf(f, "%d ", arr3[i]);
	}
	fclose(f);
}

static void execute_algorithm(int *arr, int n, void (*sort_alg)())
{
	clock_t t;
	double time_taken;
	t = clock();
	sort_alg(arr, n);
	t = clock() - t;
	time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("Time needed to sort %d elements was %f seconds\n", n, time_taken);
}

static void copy_input_arrays(int *arr1, int *arr2, int *arr3, int *sarr1, int *sarr2, int *sarr3, int n1, int n2, int n3)
{
	memcpy(arr1, sarr1, n1 * sizeof(int));
	memcpy(arr2, sarr2, n2 * sizeof(int));
	memcpy(arr3, sarr3, n3 * sizeof(int));
}

int main()
{
	/* Don't touch main */

	const int n1 = 10;
	const int n2 = 1000;
	const int n3 = 10000;
	int arr1[n1];
	int arr2[n2];
	int arr3[n3];
	int sarr1[n1];
	int sarr2[n2];
	int sarr3[n3];

	read_in_arrays_to_sort(sarr1, sarr2, sarr3, n1, n2, n3);
	copy_input_arrays(arr1, arr2, arr3, sarr1, sarr2, sarr3, n1, n2, n3);

	printf("Execution of the first alg1 algorithm\n");

	execute_algorithm(arr1, n1, alg1);
	execute_algorithm(arr2, n2, alg1);
	execute_algorithm(arr3, n3, alg1);
	write_to_file(arr1, arr2, arr3, n1, n2, n3, "out_alg1");

	copy_input_arrays(arr1, arr2, arr3, sarr1, sarr2, sarr3, n1, n2, n3);

	printf("Execution of the second alg2 algorithm\n");

	execute_algorithm(arr1, n1, alg2);
	execute_algorithm(arr2, n2, alg2);
	execute_algorithm(arr3, n3, alg2);
	write_to_file(arr1, arr2, arr3, n1, n2, n3, "out_alg2");

	copy_input_arrays(arr1, arr2, arr3, sarr1, sarr2, sarr3, n1, n2, n3);

	printf("Execution of the third alg3 algorithm\n");

	execute_algorithm(arr1, n1, alg3);
	execute_algorithm(arr2, n2, alg3);
	execute_algorithm(arr3, n3, alg3);
	write_to_file(arr1, arr2, arr3, n1, n2, n3, "out_alg3");
	return 0;
}
