#include <stdio.h>
#include <cs50.h>

void card_validation(long card);
void identify_card(long card);

int main(void){
    long card_number;
    do{
     card_number = get_long("Please enter the number written on your credit card: ");
    }while(card_number <= 0);

    card_validation(card_number);

}

void card_validation(long card){
    // store card value for later usage
    long cp_card = card;
    // start from rightmost digit
    int position = 1;
    // for digits that are even and doubled
    int sum_even = 0;
    // for digits that are odd
    int sum_odd = 0;

    while(card > 0){

// Implementing Luhn's Algorithm itself

        int digit = card % 10;  // get last digit
        card /= 10;             // remove last digit

        // if the digit is even then double the value
        if(position % 2 == 0){
            digit *= 2;

            // if the digit is more than 9
            // subtract 9 from it to make math easier
            if(digit > 9){
                digit -= 9;
            }
            // store doubled even digits
            sum_even += digit;
        }else{
            // store odd ones
            sum_odd += digit;
        }
        // move onto next digit
        position++;
    }
    // sum of both even and odd numbers
    int total = sum_even + sum_odd;

    // check if the credit card is valid or not
    if(total % 10 == 0){
        printf("card is valid \n");
        identify_card(cp_card);
    }else{
        printf("card is invalid \n");
    }
}

void identify_card(long card){
    int counter = 0;
    // use a loop to make sure only first two
    // digits remains in the end
    while(card >= 100){
        card /= 10;
        counter++;
    }
    // store the first two digits
    int first_two_digits = card;
    int length = counter + 2;
    int first_digit = ftd / 10;
    // identify card itself
    if(length == 15 && (first_two_digits == 34 || first_two_digits == 37)){
        printf("AMEX \n");
    }
    else if(length == 16 && (first_two_digits >= 51 && first_two_digits <= 55)){
        printf("MASTERCARD \n");
    }
    else if((length == 13 || length == 16) && (first_digit == 4)){
        printf("VISA \n");
    }else{
        printf("INVALID \n");
    }
}
