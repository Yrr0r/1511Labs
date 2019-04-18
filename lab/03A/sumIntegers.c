//Written by Abigail
//This program is used to print the sum of the integers from 1 to k, for all values of k between 1 and 20.

#include<stdio.h>

int main(void){
    int k,sum;
    printf(" k  sum\n\n");
    k=1;
    sum=k;
    while(k<=20){
        printf("%2d  %3d",k,sum);
        printf("\n");
        k=k+1;
        sum=sum+k;
    }
    return 0;
}

