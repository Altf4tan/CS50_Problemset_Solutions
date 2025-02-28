#include <stdio.h>
#include <cs50.h>

void print_pyramid_row(int height, int row);

int main(void){
    int height;
    do{
        height = get_int("Please enter height of pyramid: ");
    }while(height < 1 || height > 8);

    for(int row = 1; row <= height; row++){
        print_pyramid_row(height, row);
    }

}

void print_pyramid_row(int height, int row){
    for(int space = 1; space <= height - row; space++){
        printf(" ");
    }
    for(int hash = 1; hash <= row; hash++){
        printf("#");
    }
    printf("\n");
}
