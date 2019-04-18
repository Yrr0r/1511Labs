//  Exploring memory
//  Created by Richard Buckland on 2012-11-20.
//
//  Modified by:
//      Steve & Abigail
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

long add (int x, int y);

int main(void) {

    int bigInt = INT_MAX;
    int x;
    int y;
    long total;

    x = 40;
    y = 2;

    //Could have also used sizeof(int)
    printf("The variable x is located at memory address %p.\n", &x);
    printf("The variable y is located at memory address %p.\n", &y);

    total = add (x, y);

    printf("the sum of %d and %d is %ld\n", x, y, total);
    printf("The variable total is located at memory address %p.\n", &total);

    printf("sizes %d\n",sizeof(bool)); // 1
    printf("sizes %d\n",sizeof(char)); // 1
    printf("sizes %d\n",sizeof(short)); // 2
    printf("sizes %d\n",sizeof(int)); // 4
    printf("sizes %d\n",sizeof(long)); // 4
    printf("sizes %d\n",sizeof(long long)); // 8
    

    unsigned char uc = 0;   
    unsigned long ul       = 1;
    unsigned int ui        = 2;
    unsigned long long ull = 3;
    unsigned short us      = 4;

    signed char sc  = 5;
    signed long sl       = 6;
    signed int si        = 7;
    signed long long sll = 8;
    signed short ss      = 9;


    char c       = 10;
    long l       = 11;
    int i        = 12;
    long long ll = 13;
    short s      = 14;

    float f = 3.1;
    double d = 3.14;


    // add them all together just to make use of them so the compiler
    // doesn't grumble that they are unused in the program

    double grandTotal;
    grandTotal =  uc + ul + ui + ull + us +
                  sc + sl + si + sll + ss +
                   c + l  +  i +  ll +  s +
                   f + d + bigInt;
	
	printf("%p.\n", &uc);
	
    printf ("all these things added together make %f\n",
            grandTotal);

    // Add in your own variables, printf statements and arithmetic to
    // figure out the size of different types, where they live
    // and how big the numbers they store are


    return EXIT_SUCCESS;
}

long add (int x, int y) {
    long answer;
    answer = x + y;

    return answer;
}
