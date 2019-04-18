// Leap Year Stage 1
// Steve & Abigail

#include <stdio.h>

int isLeapYear(int year);

int main(void){
	printf("Enter start year: ");
	int syear;
	if(scanf("%d", &syear) == 0){
        printf("Invalid input\n");
	    return 0;
	}
	printf("Enter finish year: ");
	int fyear;
	if(scanf("%d", &fyear) == 0){
	    printf("Invalid input\n");
	    return 0;
	}
	printf("The leap years between %d and %d are:",syear,fyear);

    while(syear <= fyear){
        if(isLeapYear(syear) == 1){
	        printf(" %d",syear);
	    } 
        syear = syear+1;
    }
	printf("\n");
					
	return 0;
}

int isLeapYear(int syear){
    if(syear%4 != 0){
	    return 0;
	} else if(syear%100 != 0){
		return 1;
	} else if(syear%400 != 0){
		return 0;
	} else{
		return 1;
	}
}
