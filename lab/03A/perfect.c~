//This program is written to read a positive integer n from standard input and print all the factors of n, their sum and if indicates if n is a perfect number.
//Written by Abigail.

#include <stdio.h>
#include <math.h>

int main(void) {
    int num,i,sum,a;
    printf ("Enter number: ");
    scanf ("%d", &num);
    printf("The factors of %d are:\n", num);
    
    i = 1; 
    sum = 0;
    a = 0;
    while ( i <= num ) {
        if (num%i == 0) { 
            a = i;
            sum = sum + a;
            printf("%d\n",i);
        }
        i = i+1;
    }
    
    printf("Sum of factors = %d\n", sum);
    
    if(sum == 2*num){
        printf("%d is a perfect number",num);
    }
    else{
        printf("%d is not a perfect number",num);
    }
    printf("\n");
    
    
    return 0;
}
