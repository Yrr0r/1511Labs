
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    char cache[4096];
    printf("Enter a string: ");
    fgets(cache, 4096, stdin);
    //count:
    int i=0;
    while(cache[i] != '\0'){
        i++;
    }
    i--; // remove "\n"
    // parlindrome scan:
    for(int c=0; c<i; c++){
        if(cache[c] != cache[i-c-1]){
            printf("String is not a palindrome\n");
            exit(0);
        }
    }
    printf("String is a palindrome\n");
}
