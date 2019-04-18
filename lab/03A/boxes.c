// Boxes

#include <stdio.h>

int main(void){
    printf("How many boxes: ");
    int boxes;
    scanf("%d", &boxes);
    //
    int size = boxes*4 - 1;
    int row = 1;
    int center = 0;

    while(row<=boxes){
        center = size-2*((row-1)*2+1)+1;
        for(int i = 1; i<(row); i++){
            printf("# ");
        }
        printf("#");
        for(int i = 1; i<center ; i++){
            printf("#");
        }
        printf("#");
        for(int i = 1; i<(row); i++){
            printf(" #");
        }
        printf("\n");
        //
        for(int i = 1; i<(row); i++){
            printf("# ");
        }
        printf("#");
        for(int i = 1; i<center;i++){
            printf(" ");
        }
        printf("#");
        for(int i = 1; i<(row); i++){
            printf(" #");
        }
        printf("\n");
        //
        row ++;
    }
    row = boxes;
        for(int i = 1; i<(row); i++){
            printf("# ");
        }
        printf("###");
        for(int i = 1; i<(row); i++){
            printf(" #");
        }
        printf("\n");

    row = boxes - 1;

    while(row>0){
        center = size-2*((row-1)*2+1)+1;
        for(int i = 1; i<(row); i++){
            printf("# ");
        }
        printf("#");
        for(int i = 1; i<center;i++){
            printf(" ");
        }
        printf("#");
        for(int i = 1; i<(row); i++){
            printf(" #");
        }
        printf("\n");
        //
        for(int i = 1; i<(row); i++){
            printf("# ");
        }
        printf("#");
        for(int i = 1; i<center ; i++){
            printf("#");
        }
        printf("#");
        for(int i = 1; i<(row); i++){
            printf(" #");
        }
        printf("\n");
        //
        row --;
    }
}
