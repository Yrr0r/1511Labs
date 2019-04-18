//Written by Steve & Abigail
//Count 5

#include<stdio.h>

int main(void){
	int value;
	printf("Please enter an integer: ");
	scanf("%d",&value);

	if(value == 1){
		printf("You entered one. \n");
	} else if(value == 2){
		printf("You entered two. \n");
	} else if(value == 3) {
		printf("You entered three. \n");
			}else if(value == 4){
		printf("You entered four. \n");
			}else if(value == 5){ 
		printf("You entered five. \n");
			}else if(value < 1){
		printf("You entered a number less than one. \n");
	} else {
		printf("You entered a number greater than five. \n");
	}
	return 0;
}


