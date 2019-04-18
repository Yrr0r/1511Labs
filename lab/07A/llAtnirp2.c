#define MAX_LENGTH 20
#define MAX_ROWS 100
#define EXIT_SUCCESS 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tnirp(FILE *wfile, char cache[]);
void llAtnirp(FILE *wfile, char text[][MAX_LENGTH],int numLines);
void readFrom(FILE *stream, char cache[][MAX_LENGTH], int *numLines);

int main(int argc, char * argv[]){
    char cache[MAX_ROWS][MAX_LENGTH];
    int count;
    
    // To Read
    if(argc == 1){
    	printf("Enter up to 100 strings: \n");
    	readFrom(stdin,cache,&count); // Counts are pointers to reserve value
    } else {
    	FILE *inputf;
    	inputf = fopen(argv[1],"r");
    	if(inputf == NULL){
    		fprintf(stderr, "Could not open file\n");
    		exit(EXIT_FAILURE);
    	}
    	readFrom(inputf,cache,&count);
    }
    
    // To Output
    if(argc == 3){
    	FILE *outputf;
    	outputf = fopen(argv[2], "w");
    	llAtnirp(outputf, cache, count); // This time count is a int
    } else {
    	llAtnirp(stdout, cache, count);
    }
    
    return EXIT_SUCCESS;
}

void readFrom(FILE *stream, char cache[][MAX_LENGTH], int *numLines){
    char buffer[MAX_LENGTH];
    int count = 0;
    while(fgets(buffer,MAX_LENGTH,stream)!= NULL){
    	for(int i=0; i<MAX_LENGTH; i++){
    		cache[i][count] = buffer[i];
    	}
    	count++;
    }
    *numLines = count;
}

void llAtnirp(FILE *wfile, char text[][MAX_LENGTH],int numLines){
	char buf[MAX_LENGTH];
    for(int i=(numLines-1); i>=0; i--){
    	for(int t=0; t<MAX_LENGTH; t++){
    		buf[t] = text[t][i];
    	}
    	tnirp(wfile, buf);
    }
}

void tnirp(FILE *wfile, char cache[]){
    int i=0;
    while(cache[i] != '\0'){
        i++;
    }
    for(int c=i; c>=0; c--){
        if(cache[c] != '\0' && cache[c] != '\n'){
        	fprintf(wfile, "%c", cache[c]);
        }
    }
    fprintf(wfile, "\n");
}
