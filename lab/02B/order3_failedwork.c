// Steve, Exc3
// Written using for loop, not if
// This is a failed work

#define numIntegers 3 //define how many numbers to compare.

#include <stdio.h>

int maxval(int arr[]){
	int tmpMax = 0;
	int counter = 1;
	
	while (tmpMax < arr[(counter)] && counter < (numIntegers-1)){
	counter ++;
	}
	
	return tmpMax;
}


int main(void){
	int intlist[numIntegers];
	int tranVal;
	int out[numIntegers];
	for(int i=0; i<numIntegers; i++){
		printf("Enter integer:");
		scanf("%d", &tranVal);
		intlist[i] = tranVal;
	}
	
	for(int i=0; i<numIntegers; i++){
		out[i] = maxval(intlist);
	}
	printf("The integers in order are: ");
	for(int i=0; i<numIntegers; i++){
		printf("%d ", out[i]);
	}
	
}

