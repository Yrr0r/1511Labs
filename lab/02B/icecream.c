// PROGRAM TEMPLATE
// Steve

#include <stdio.h>

int main(void){
	int scoops;
	int price;
	int money = 10;
	printf("How many scoops? ");
	scanf("%d", &scoops);
	printf("How many dollars does each scoop cost? ");
	scanf("%d", &price);
	
	if((scoops*price)<=money){
		printf("You have enough money!\n");
		} else {
			printf("Oh no, you don't have enough money :( \n");
			}
	
	return 0;
	
}
