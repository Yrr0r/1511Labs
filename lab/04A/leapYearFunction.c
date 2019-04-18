// Leap Year Stage 1
// Steve & Abigail

#include <stdio.h>

int isLeapYear(int year);

int main(void){
	printf("Enter year: ");
	int year;
	scanf("%d", &year);
	//
	if(isLeapYear(year) == 1){
	    printf("%d is a leap year.",year);
	} else{
	    printf("%d is not a leap year.",year);
	}
	printf("\n");
					
	return 0;
	
}

int isLeapYear(int year){
    if(year%4 != 0){
		return 0;
	} else if(year%100 != 0){
		return 1;
	} else if(year%400 != 0){
		return 0;
	} else{
		return 1;
	}
	
}
