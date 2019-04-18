#define MAX_LENGTH 20
#define MAX_ROWS 100
#define EXIT_SUCCESS 0

#include <stdio.h>
#include <string.h>

void tnirp(char cache[]);
void llAtnirp(char text[][MAX_LENGTH],int numLines);

int main(int argc, char * argv[]){
    char cache[MAX_ROWS][MAX_LENGTH];
    printf("Enter up to 100 strings: \n");
    
    char buffer[MAX_LENGTH];
    int count = 0;
    while(fgets(buffer,MAX_LENGTH,stdin)!= NULL){
    	for(int i=0; i<MAX_LENGTH; i++){
    		cache[i][count] = buffer[i];
    	}
    	count++;
    }
    llAtnirp(cache,count);
    

    return EXIT_SUCCESS;
}

void llAtnirp(char text[][MAX_LENGTH],int numLines){
	char buf[MAX_LENGTH];
    for(int i=(numLines-1); i>=0; i--){
    	for(int t=0;t<MAX_LENGTH; t++){
    		buf[t] = text[t][i];
    	}
    	tnirp(buf);
    }
}

void tnirp(char cache[]){
    int i=0;
    while(cache[i] != '\0'){
        i++;
    }
    for(int c=i; c>=0; c--){
        if(cache[c] != '\0' && cache[c] != '\n'){
            putchar(cache[c]);
        }
    }
    printf("\n");
}
