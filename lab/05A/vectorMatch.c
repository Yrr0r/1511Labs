#include <stdio.h>

#define SIZE 10
int main(void){
	int vec1[SIZE];
	printf("Enter vector 1 of 10 positive numbers: ");
	for(int i=0; i<10; i++){
		scanf("%d", &vec1[i]);
	}
	int vec2[10];
	printf("Enter vector 2 of 10 positive numbers: ");
	for(int i=0; i<10; i++){
		scanf("%d", &vec2[i]);
	}
	int match = 0;
	for(int i=0; i<10; i++){
		if(vec1[i]==vec2[i]){
			match++;
		}
	}
	printf("Vectors match in %d positions.\n", match);
}

