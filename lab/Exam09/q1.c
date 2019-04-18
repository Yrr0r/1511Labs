#include <stdio.h>

int main(void){
	int count = 0;
	char ch = getchar();
	while(ch != EOF){
		if(ch >= '0' && ch <= '9'){
			count ++;
		}
		ch = getchar();
	}
	printf("%d digits. \n", count);
}
