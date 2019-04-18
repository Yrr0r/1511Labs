#define MAX_LENGTH 20
#define EXIT_SUCCESS 0;

#include <stdio.h>
#include <string.h>

void tnirp(char cache[]);

int main(int argc, char * argv[]){
    char s[MAX_LENGTH];
    
    printf("Enter String\n");
    // fgets returns NULL if it gets only a ctrl ^d
    if( fgets(s,MAX_LENGTH,stdin) != NULL ){
        tnirp(s);
    }
    return EXIT_SUCCESS;
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
