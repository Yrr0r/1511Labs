// Written by Steve & Abigail
//Date:16/01/2019
//This program is used to calculate the area of a triangle.

#include <stdio.h>
#include <math.h>

int main(void){
	double a,b,c, area,s;
	printf("Enter side 1:");
	scanf( "%lf", &a);
	printf("Enter side 2:");
	scanf( "%lf", &b);
	printf("Enter side 3:");
	scanf( "%lf", &c);

	s = (a + b + c)/2;
	if((s*(s-a)*(s-b)*(s-c)) < 0){
		printf("Error: triangle inequality violated.\n");
	} else {
		area = sqrt(s*(s-a)*(s-b)*(s-c));
		printf("Area = %lf \n" , area);
	}
    return 0;
}
