#include <cs50.h>
#include <stdio.h>
/*
**Selection Sort(O(n squared))
1. Repeat until no unsorted elements remain
  1.1 Search the unsorted part of the data to find the smallest value
  1.2 Swap the smallest found value with the first element of the unsorted part
*Pseudo-code:
SelectionSort(array):
    for i = 0 to n - 1:
        smallest = i
        for j = i + 1 to n - 1:
            if array[j] < array[smallest]:
                smallest = j
        Swap(array[i], array[smallest])

*Worst-case scenario: We have to iterate over each of the n
elements of the array (to find the smallest unsorted
element) and we must repeat this process n times, since only
one element gets sorted on each pass.

*Best-case scenario: Exactly the same! There’s no way to
guarantee the array is sorted until we go through this
process for all the elements.

*/
int main(void)
{
  // Unsorted array
  int numbers[] = {6, 1, 2, 78, 12, 45, 793, 191, 38, 90};
  // Get the true size of array
  int size = sizeof(numbers) / sizeof(numbers[0]);
  for (int i = 0; i < size - 1; i++)
  {
    // Find the smallest element in the unsorted portion
    int smallest = i;
      for (int j = i + 1; j < size; j++)
      {
        if (numbers[j] < numbers[smallest])
        {
          smallest = j;
        }
      }
      // Swap the smallest element with current one
      int temp = numbers[i];
      numbers[i] = numbers[smallest];
      numbers[smallest] = temp;
    }
    for (int m = 0; m < size; m++)
    {
      printf("%i ", numbers[m]);
    }
    printf("\n");

}

