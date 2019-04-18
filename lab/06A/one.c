
#include <stdio.h>
#include <string.h>

int main(void){
    char cache[4096];
    printf("Enter a string: ");
    fgets(cache, 4096, stdin);
    int i=0;
    while(cache[i] != '\0'){
        if(cache[i]!='\n'){
            putchar(cache[i]);
            printf("\n");
        }
        i++;
    }
    
}
