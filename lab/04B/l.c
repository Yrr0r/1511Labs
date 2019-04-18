// q2 L by Steve

#include <stdio.h>

int main(void){
	printf("Enter size: ");
	int n;
	if(scanf("%d", &n) == 1){
		for (int i=(n-2); i >= 0; i--){
			printf("* \n");
		}
		for (int i=n; i >= 1; i--){
			printf("*");
		}
		printf("\n");
	}
	
	return 0;
}
