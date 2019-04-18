
#include <stdio.h>
#include <string.h>

int main(){
    char ch;
    float counter = 0;
    int count[26] = {0};
    
    ch = getchar();
    
    while(ch != EOF){
        if(ch > 'A' && ch < 'Z'){
            count[ch-'A']++;
            counter = counter +1;
        } else if(ch > 96 && ch < 123){
            count[ch-97]++;
            counter = counter + 1;
        }
        ch = getchar();
    }
    
    for(int i=0; i<26; i++){
        printf("\'%c\' %lf %d \n",i+0x61,count[i]/counter ,count[i]);
    }
}

