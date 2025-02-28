#include <cs50.h>
#include <stdio.h>

int factorial(int number);

int main(void)
{
    int number = get_int("Number: ");
    int result = factorial(number);
    printf("factorial of %i is %i\n", number, result);
}

int factorial(int number)
{
    // Base case
    if (number == 0)
    {
        return 1;
    }
    // Recursive case
    else
    {
        // number = 4
        // f(1) = 1
        // f(2) = 2 => 2 * f(1)
        // f(3) = 6 => 3 * f(2)
        // f(4) = 24 => 4 * f(3)
        return number * factorial(number - 1);
    }
}
