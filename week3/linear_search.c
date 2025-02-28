#include <cs50.h>
#include <stdio.h>

// Linear Search(O(n))
// Looks every element one-by-one in unsorted array
// Until given number is found
// Worst-case scenario: looks every index; finds it in the end
// or cannot find it
// Best-case scenario: finds the given element in the first index

int main(void)
{
    int numbers[] = {1,45,23,68,93,12,30,38,58};
    int search = get_int("Number to search for: ");
    for (int i = 0, size = sizeof(numbers); i < size; i++)
    {
        if (search == numbers[i])
        {
            printf("%i found at %i.\n", search, i);
            return 0;
        }
    }
    printf("did not found %i in list.\n", search);
    return 1;
}
