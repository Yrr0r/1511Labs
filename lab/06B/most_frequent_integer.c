#define MAX 100000

#include <stdio.h>
static int countfreq(int size, int list[MAX], int num);

int main(void){
	int list[MAX];
	int input;
	int lscount = 0;
	while(scanf("%d", &input) == 1){
		list[lscount] = input;
		lscount ++;
	}
	// Begin judgement
	int size = lscount;
	int maxfreq = 0;
	int thenumber;
	for(int i=0; i<size; i++){
		if(countfreq(size, list, list[i]) > maxfreq){
			thenumber = list[i];
			maxfreq = countfreq(size, list, list[i]);
		}
		if(countfreq(size, list, list[i]) == maxfreq){
			if(list[i] > thenumber){
				thenumber = list[i];
			}
		}
	}
	printf("%d\n", thenumber);
	
}

static int countfreq(int size, int list[MAX], int num){
	int count = 0;
	for(int i=0; i<size; i++){
		if(list[i] == num){
			count++;
		}
	}
	return count;
}
