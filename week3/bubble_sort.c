#include <cs50.h>
#include <stdio.h>
// Bubble sorting(O(n squared))
/*
* In bubble sort, the idea of the algorithm is to move higher valued
elements generally towards the right and lower value elements
generally towards the left.

** Worst-case scenario: The array is in reverse order; we have
to “bubble” each of the n elements all the way across the array,
and since we can only fully bubble one element into
position per pass, we must do this n times.

** Best-case scenario: The array is already perfectly sorted,
and we make no swaps on the first pass.

* Pseudo-code V1
1. Set swap counter to a non-zero value
2. Repeat until the swap counter is 0:
3. Reset swap counter to 0
4. Look at each adjacent pair
5. If two adjacent elements are not in order,
   swap them and add one to the swap counter

* Pseudo-code V2
BubbleSort(array):
    Repeat for (n - 1) passes:
        For i = 0 to n - 2:
            If array[i] > array[i + 1]:
                Swap(array[i], array[i + 1])
        If no swaps are made in a pass, list is sorted; break early

*/
int main(void)
{
    // Unsorted array
    int numbers[] = {7,2,3,2,5,6,3,9,1,10};

    // Get true size of the array
    int size = sizeof(numbers) / sizeof(numbers[0]);

    // Outer loop repeating for (n - 1) passes
    for (int i = 0; i < size; i++)
    {
        // Create a swap counter for each swap made in array
        int swap_counter = 0;
        // Inner loop repeating for (n - 2) passes for making sure
        // each element is compared and swapped if necessary
        for (int j = 0; j < size - 1; j++)
        {
            // If current number is greater than next number swap them
            if (numbers[j] > numbers[j + 1])
            {
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
                // Add one to counter each time swap made
                swap_counter++;
            }
        }
        // If there was no swaps stop
        if (swap_counter == 0)
        {
            break;
        }
    }
    printf("Sorted numbers: ");
    for (int k = 0; k < size; k++)
    {
        printf("%i ", numbers[k]);
    }
    printf("\n");
}

