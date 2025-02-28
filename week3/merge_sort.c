#include <cs50.h>
#include <stdio.h>
/*Merge Sort(O(n log n))
In merge sort, the idea of the algorithm is to sort smaller
arrays and then combine those arrays together (merge them) in sorted order.
Merge sort leverages something called recursion, which we’ll touch on in more detail in a future
video.

In pseudocode:
1. Sort the left half of the array (assuming n> 1)
2. Sort the right half of the array (assuming n> 1)
3. Merge the two halves together

Pseudocode V2:
MergeSort(array, left, right):
    If left >= right:
        Return  // Base case: If the array has one or zero elements, it's already sorted

    // Step 1: Divide the array into two halves
    middle = (left + right) / 2

    // Step 2: Recursively sort both halves
    MergeSort(array, left, middle)
    MergeSort(array, middle + 1, right)

    // Step 3: Merge the sorted halves
    Merge(array, left, middle, right)

------------------------------------------

Merge(array, left, middle, right):
    // Step 1: Determine sizes of the subarrays
    n1 = middle - left + 1  // Size of left subarray
    n2 = right - middle     // Size of right subarray

    // Step 2: Create temporary subarrays
    LeftArray[0...n1-1] = elements from array[left...middle]
    RightArray[0...n2-1] = elements from array[middle+1...right]

    // Step 3: Merge the temporary arrays back into the main array
    i = 0  // Pointer for LeftArray
    j = 0  // Pointer for RightArray
    k = left  // Pointer for merged array

    While i < n1 AND j < n2:
        If LeftArray[i] <= RightArray[j]:
            array[k] = LeftArray[i]
            i = i + 1
        Else:
            array[k] = RightArray[j]
            j = j + 1
        k = k + 1

    // Step 4: Copy any remaining elements of LeftArray
    While i < n1:
        array[k] = LeftArray[i]
        i = i + 1
        k = k + 1

    // Step 5: Copy any remaining elements of RightArray
    While j < n2:
        array[k] = RightArray[j]
        j = j + 1
        k = k + 1
        
*Worst-case scenario: We have to split nelements up and then recombine them,
effectively doubling the sorted subarrays as we build them up.
 (combining sorted 1-element arrays into 2-element arrays,
  combining sorted 2-element arrays into 4-element arrays…)

*Best-case scenario: The array is already perfectly sorted.
But we still have to split and recombine it back together with this algorithm.
*/
void merge_sort(int array[], int left, int right);
void merge(int array[], int left, int middle, int right);

int main(void)
{
    int array[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(array) / sizeof(array[0]);

    merge_sort(array, 0, n - 1);

    // Print sorted array to verify
    for (int i = 0; i < n; i++)
    {
        printf("%i ", array[i]);
    }
    printf("\n");

    return 0;
}

void merge_sort(int array[], int left, int right)
{
    // If the array has one or zero elements its already sorted
    if (left >= right)
    {
        return;
    }
    //  Divide the array into two halves
    int mid = (left + right) / 2;

    // Recursively sort both halves
    merge_sort(array, left, mid);
    merge_sort(array, mid + 1, right);

    // Merge sorted halves
    merge(array, left, mid, right);
}

void merge(int array[], int left, int middle, int right)
{
    // Determine size of subarrays
    // Left array size
    int left_size = middle - left + 1;
    // Right array size
    int right_size = right - middle;

    // Create temporary subarrays
    int left_copy[left_size];
    int right_copy[right_size];

    // Copy left side
    for (int n = 0; n < left_size; n++)
    {
        left_copy[n] = array[left + n];
    }

    // Copy right side
    for (int m = 0; m < right_size; m++)
    {
        right_copy[m] = array[middle + 1 + m];
    }

    // Merge the temporary arrays back into the main array
    //  i => Left array pointer
    //  j => right array pointer
    //  k => pointer for merged array
    int i = 0, j = 0, k = left;

    while (i < left_size && j < right_size)
    {
        if (left_copy[i] <= right_copy[j])
        {
            array[k] = left_copy[i];
            i = i + 1;
        }
        else
        {
            array[k] = right_copy[j];
            j = j + 1;
        }
        k = k + 1;
    }
    // Copy remaining elements of left array
    while (i < left_size)
    {
        array[k] = left_copy[i];
        i = i + 1;
        k = k + 1;
    }
    // Copy remaining elements of right array
    while (j < right_size)
    {
        array[k] = right_copy[j];
        j = j + 1;
        k = k + 1;
    }
}
