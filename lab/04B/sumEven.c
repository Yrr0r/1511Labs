// q3 SumEven by Steve

#include <stdio.h>

int main(void){
	int sum = 0;
	int buf = 1;
	while(scanf("%d", &buf) && buf >= 0){
		
		if(buf % 2 == 0){
			sum = sum + buf;
		}
	}
	printf("Sum of even numbers was: %d\n" , sum);
	
	return 0;
	
}
