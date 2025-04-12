#include <cs50.h>
#include <stdio.h>
/*
*The Collatz conjecture is applies to positive integers and speculates
that it is always possible to get “back to 1” if you follow these steps:

1. If n is 1, stop.
2. Otherwise, if n is even, repeat this process on n/2.
3. Otherwise, if n is odd, repeat this process on 3n+ 1.

*Write a recursive function collatz(n) that calculates how many steps
it takes to get to 1 if you start from n and recurseas indicated above.
*/
int collatz(int n);
int main(void)
{
    int n = 12;
    printf("numbers taken to reach from %i to 1 is %i\n", n, collatz(n));
}

int collatz(int n)
{
    // If n is 1 stop
    if (n == 1)
        return 0;
    // If n is even, divide n with 2
    else if (n % 2 == 0)
        // We are adding 1 to collatz() for counting each step to reach 1
        return 1 + collatz(n / 2);
    // If n is odd, multiply n with 3 add 1
    else
        return 1 + collatz(3 * n + 1);
}
