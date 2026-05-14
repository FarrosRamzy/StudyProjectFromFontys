#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include "number_sort_handler.h"

///////////////////////////////////////////////////////////////
//<Assignment 1.2 sorting algorithm>
//(sorting_handler_file)
//
// Course		: SD
// Student		: Farros Ramzy (3767353)
// Date			: 15-09-2023
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
int check_size_of_list(int size_of_input)
{
    if (size_of_input < MIN_SIZE_OF_ARRAY || size_of_input > MAX_SIZE_OF_ARRAY)
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
    if (input_val < MIN_INPUT_VAL || input_val > MAX_INPUT_VAL)
    {
        return 0;
    }

    return 1;
}

/**
 * @brief Input array's adder.
 *
 * @note This function is responsible to populate the intended array with the
 * 		 scanned input values by their queue number.
 *
 * @param input_array The array where the input value will be placed in.
 * @param queue_in_array The position of the array where the input number will be placed.
 * @param input_val The valid input numbers which will populate the array.
 */
void add_input_to_array(int *input_array, int queue_in_array, int input_val)
{
    (*(input_array + queue_in_array)) = input_val;
}

/**
 * @brief SUM size limit checker.
 * 
 * @note This function is responsible to check if the SUM range for the intended array is within
 *       its acceptable min and max restriction or not.
 * 
 * @param size_val The SUM range checker.
 * @return int 0 when the input is invalid and 1 only if the input is valid.
 */
int check_size_of_sum(int size_val)
{
    if (size_val < MIN_SIZE_OF_SUM || size_val > MAX_SIZE_OF_SUM)
    {
        return 0;
    }
    return 1;
}

/**
 * @brief A sorting function.
 * 
 * @note This function is a bubble sort function. This function is resposible to sort the values
 *       within the input array from its lowest number to the highest.
 * 
 * @param input_array The array of numbers.
 * @param size_of_array 
 */
void sort_array_elements(int *input_array, int size_of_array)
{
    int temporary = 0;
    for (int i = 0; i < size_of_array; i++)
    {
        for (int j = i+1; j < size_of_array; j++)
        {
            if (*(input_array + i) > *(input_array + j))
            {
                temporary = *(input_array + i);
                *(input_array + i) = *(input_array +j);
                *(input_array +j) = temporary;
            }
        }
    }
}

/**
 * @brief SUM difference's finder.
 * 
 * @note This function is responsible to calculate the min and max SUM values within the array
 *       before calculating the difference between the two SUMs and return its value to the
 *       caller of this function.
 * 
 * @param input_array The array of numbers.
 * @param size_of_array
 * @param size_of_sum 
 * @return int value of difference between the two SUM values.
 */
int get_difference_val_of_min_max(int *input_array, int size_of_array, int size_of_sum)
{
    int min_sum_val = 0;
    int max_sum_val = 0;
    
    int diff_val = 0;

    int range = size_of_array-1;

    for (int i = 0; i < size_of_sum; i++)
    {
        max_sum_val += *(input_array + (range - i));
        min_sum_val += *(input_array + i);
    }
    
    diff_val = max_sum_val - min_sum_val;

    return diff_val;
}