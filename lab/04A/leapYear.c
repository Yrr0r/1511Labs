// Leap Year Stage 1
// Steve & Abigail

#include <stdio.h>

int main(void){
	printf("Enter year: ");
	int year;
	scanf("%d", &year);
	//
	if(year%4 != 0){
		printf("%d is not a leap year.\n", year);
	} else if(year%100 != 0){
		printf("%d is a leap year.\n", year);
	} else if(year%400 != 0){
		printf("%d is not a leap year.\n", year);
	} else{
		printf("%d is a leap year.\n", year);
	}
					
	return 0;
	
}

