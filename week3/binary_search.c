#include <cs50.h>
#include <stdio.h>

/* Binary Search(O(log n))

*In binary search, the idea of the algorithm is to divide and conquer,
*reducing the search area by half each time, trying to find a target number.

**In order to leverage this power however, our array must first be sorted,
**else we cannot make assumptions about the array’s contents.

** Worst-case scenario:
We have to divide a list of n elements in half repeatedly to find the
target element, either because the target element will be found at the
end of the last division or doesn't exist in the array at all

** Best-case scenario:
The target element is at the midpoint of the full array, and so we can stop
looking immediately after we start

* Pseudo-code
Initialize low to 0
Initialize high to length of array - 1

While low is less than or equal to high
    Calculate mid as (low + high) / 2
    If array[mid] equals target
        Return mid
    Else if array[mid] is less than target
        Set low to mid + 1
    Else
        Set high to mid - 1

Return target not found
*/
int main(void)
{
    // Create a sorted array for Binary Search
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Initialize lowest point to 0(n)
    int low = 0;

    // Store true size of the array
    int size = sizeof(numbers) / sizeof(numbers[0]);

    // Initialize highest point to array_size - 1(n - 1)
    int high = size - 1;
    int search = get_int("Number to search for: ");

    // Create a loop until lowest point exceeds highest point
    while (low <= high)
    {
        // Calculate the middle point
        int mid = (low + high) / 2;

        // Stop when we find the given element
        if (numbers[mid] == search)
        {
            printf("%i found\n",search);
            return 0;
        }
        // Narrow search to left side of the array
        else if (numbers[mid] > search)
        {
            high = mid - 1;
        }
        // Narrow search to right side of the array
        else if (numbers[mid] < search)
        {
            low = mid + 1;
        }
    }
    printf("%i not found\n", search);
    return 1;
}
