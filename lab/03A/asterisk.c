// Steve & Abigail
// Asterisk

#include <stdio.h>

int main(void){
    int size;
    printf("Enter size: ");
    scanf("%d", &size);
    // error catch here
    int middle = (size/2)+1;
    int left = 1;
    int right = size;
    int row = 1;
    int column = 1;
    while(row <= (size+1)){
        //printf("*");
        while(column <= size){
            
            if(column == left){
                printf("*");
            } else if(column == right){
                printf("*");
            } else if(column == middle){
                printf("*");
            } else if(row == middle){
                for(int i=0;i<size;i++){
                    printf("*");
                }
                row ++;
                break;
            } else{
                printf("-");
            }
            column ++;
        }
        printf("\n");
        column = 1;
        row ++ ;
        left ++;
        right --;
        
    }
}
