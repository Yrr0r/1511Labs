//Written by Abigail
//This program is used to print the sum of the cubes of the integers from 1 to k, for all values of k between 1 and 20.

#include<stdio.h>
#include<math.h>

int main(void){
    int k,cube;
    int sum=0;
    printf(" k  cubes\n\n");
    k=1;
    
    while(k<=20){
        sum = k + sum;
        cube = sum * sum;
        printf("%2d  %5d",k,cube);
        printf("\n");
        k=k+1;

    }
    return 0;
}
