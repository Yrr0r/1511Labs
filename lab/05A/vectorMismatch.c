#include <stdio.h>

int main(void){
    // Vec input:
	int vec1[10];
	printf("Enter vector 1 of 10 positive numbers: ");
	for(int i=0; i<10; i++){
		scanf("%d", &vec1[i]);
	}
	int vec2[10];
	printf("Enter vector 2 of 10 positive numbers: ");
	for(int i=0; i<10; i++){
		scanf("%d", &vec2[i]);
	}
	// Match
	int match = 0;
	for(int i=0; i<10; i++){
		if(vec1[i]==vec2[i]){
			match++;
		    vec1[i] = -1;
		    vec2[i] = -1;
		}
	}
	// Mismatch
	int miss = 0;
	for(int i=0; i<10; i++){
	    for(int p=0; p<10; p++){
	        if((vec1[i]>=0 && vec2[i]>=0) && (vec1[i] == vec2[p])){
	            miss++;
	            vec1[i] = -1;
	            vec2[i] = -1;
	        }
	    }
	}
	
	printf("Vectors match in %d positions.\n", match);
	printf("Vectors mismatch in %d positions.\n", miss);	
	
}

