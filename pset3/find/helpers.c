/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"


// Declare findMidPoint
int findMidPoint(int min, int max)
{
    /* findMidPoint - Computes mid point between two numbers
    
    INPUTS:
        min:        int scalar, Mininum number
        max:        int scalar, Maximum number
    
    OUTPUTS:
        midPoint:   int scalar, Midpoint between min and max
    
    Date: 08-13-2016
    Name: Sean M Hamlet
    */
    int midPoint = (max + min) / 2;
    
    return midPoint;
}

// Declare Binary Search
bool binarySearch(int key, int array[], int min, int max)
{
    /* binarySearch - Recursively searches for key in array with Binary Search
    
    INPUTS:
        key:        int scalar, Value to search in array
        array[]:    int array, Array of values to be sorted
        min:        int scalar, Min index to search
        max:        int scalar, Max index to search
    
    OUTPUTS:
        bool:       bool, True/False value indicating key found (true)
                    or not found (false)
    
    Date: 08-13-2016
    Name: Sean M Hamlet
    */
    
    int midPoint;
    
    // Gone too far, key not in array
    if (max < min)
    {
        return false;
    } else
    {
        midPoint = findMidPoint(min, max);
        
        if (array[midPoint] < key)
        {
            return binarySearch(key, array, midPoint + 1, max);
        } else if (array[midPoint] > key)
        {
            return binarySearch(key, array, min, midPoint - 1);
        } else if (array[midPoint] == key)
        {
            return true;
        }
        
        return false;
    }
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    /* search - Searches array of values for particular value
    
    INPUTS:
        value:      int scalar, Value to be searched
        values[]:   int array, Array of values to be searched
        n:          int scalar, Size of array to be sorted
    
    OUTPUTS:
        bool:       bool, True/False if value was found / not found
    
    Date: 08-13-2016
    Name: Sean M Hamlet
    */
    
    // Perform Binary Search
    return binarySearch(value, values, 0, n - 1);
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    /* sort - Sorts array using Selection Sort
    
    INPUTS:
        values[]:   int array, Array of values to be sorted
        n:          int scalar, Size of array to be sorted
    
    OUTPUTS:
        values[] (sorted):  int array, Since array is passed by reference and
                            not by value, the array is implicitly returned sorted
    
    Date: 08-13-2016
    Name: Sean M Hamlet
    */
    
    // TODO: implement an O(n^2) sorting algorithm
    // Selection Sort
    int minIndex;
    int iValue;
    int minValue;
    // for i = 0 to n - 1
    for (int i = 0; i < n - 1; i++)
    {
        // for j = i + 1 to n
        minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (values[j] < values[minIndex])
            {
                minIndex = j;
            }
            // find index of minimum value
        }
        
        // swap array[min] and array[i]
        minValue = values[minIndex];
        iValue = values[i];
        values[i] = minValue;
        values[minIndex] = iValue;
    }

    return;
}