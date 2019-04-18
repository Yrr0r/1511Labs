// Written by Steve & Abigail
// Prism

// To comply with 2000*2000*2000, could use unsighed long int instead of int type. Type 'int' has limit 

#include <stdio.h>

int main(void){
	int length;
	int width;
	int height;
	printf("Please enter prism length: ");
	scanf("%d", &length);
	printf("Please enter prism width: ");
	scanf("%d", &width);
	printf("Please enter prism height: ");
	scanf("%d", &height);
	printf("A prism with sides %d %d %d has:\n", length, width, height);
	printf("Volume      = %d", (length*width*height));
	printf("\nArea        = %d", (2*(length*width+width*height+height*length)));
	printf("\nEdge length = %d", 4*(length+width+height));
	printf("\n");
	return 0;
}

