//A program that reads an integer n from standard input,prints an n*n pattern ofasterisks and dashes in the shape of an"+"
//Written by Abigail
//On 2019/01/23


#include <stdio.h>

int main(void){
    int number;
    int row, column;

    // Obtain input
    printf("Enter size: ");
    scanf("%d",&number);

    row = 1;
    if(number%2 ==1 && number >= 5){
         while (row <= number) {
            column = 1;
            while (column <= number) {
                if(row == (number-1)/2 +1 ||column == (number-1)/2 +1){
                	printf("*");
                }
                else{
                	printf("-");
                }
            column = column + 1;
            }
            printf("\n");
            row = row + 1;
        }
    }
    return 0;
}
