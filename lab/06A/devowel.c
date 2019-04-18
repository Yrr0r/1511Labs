
#include <stdio.h>
#include <string.h>

int main(void){
    char i;
    i = getchar();
    while(i != EOF){
        if(i != 'a' && i!='e' && i!='i' && i!='o'&& i!='u'){
            putchar(i);
        }
        i = getchar();
    }
}
