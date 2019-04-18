// q1 Countdown by Steve

#include <stdio.h>

int main(void){
	printf("Enter n: ");
	int n;
	if(scanf("%d", &n) == 1){
		while (n >= 0){
			printf("%d \n" , n);
			n--;
		}
	}
	
	return 0;
}
