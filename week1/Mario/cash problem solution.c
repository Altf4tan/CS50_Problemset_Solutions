
#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Define the certain values for each term
#define quarter 25
#define dime 10
#define nickel 5
#define penny 1

int main(void){
    int change_in_cents, coins = 0;
    do{
        // Input in cents
        change_in_cents = get_int("Change owed: ");

    }while(change_in_cents < 0);

    // Calculate the number of coins
    coins += change_in_cents / quarter;
    change_in_cents %= quarter;

    coins += change_in_cents / dime;
    change_in_cents %= dime;

    coins += change_in_cents / nickel;
    change_in_cents %= nickel;

    coins += change_in_cents / penny;

    printf("%d\n", coins);

}
