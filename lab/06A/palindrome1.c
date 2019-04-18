
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    char cache[4096];
    printf("Enter a string: ");
    
    char ch;
    int count=0;
    ch = getchar();
    while(ch != EOF){
        if(ch > 64 && ch < 91){
            cache[count] = ch+32;
            count++;
        } else if(ch > 96 && ch < 123){
            cache[count] = ch;
            count++;
        }
        ch = getchar();
    }
    cache[count+1] = '\0';
    
    //count:
    int i=count; //Modifyed from prev program.
    // parlindrome scan:
    for(int c=0; c<i; c++){
        if(cache[c] != cache[i-c-1]){
            printf("String is not a palindrome\n");
            exit(0);
        }
    }
    printf("String is a palindrome\n");
}
