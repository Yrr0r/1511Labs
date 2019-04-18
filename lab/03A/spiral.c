// Spiral, Group Steve & Abigail
// SPIRAL

#include <stdio.h>
#include <stdbool.h>

//Declare Func
void drawside(int input);
void drawmid(int input, bool bw);
int nthodd(int input);
void singleLine(int size, int left, int right,int bw);
void specialLine(int size, int starcount);
void bigSpiral(int size);
void smallSpiral(int size);
void superTinyCuteSpiral(int size);

int main(void){
    int size;
    printf("Enter size:");
    scanf("%d",&size);
    // Input End
    if(size < 9){
        superTinyCuteSpiral(size);
    } else if ((size > 9) && (((size-7)%4) == 0)){
        bigSpiral(size);
    } else {
        smallSpiral(size);
    }
    
}

void superTinyCuteSpiral(int size){
    int starcount = (size/4);
    // First half
    for(int i=1; i<=(starcount); i++){
        singleLine(size, i-1, i, 1);
        printf("\n");
        singleLine(size, i-1, i, 0);
        printf("\n");
    }
    if(size == 7){
        singleLine(size, starcount, starcount+1, 1);
        printf("\n");
        printf("*---*-*\n");
        singleLine(size, starcount+1,starcount+1, 1);
        printf("\n");
    }
    if(size == 5){
        printf("***-*\n");
    }
    // Last half
    for(int i=starcount; i>=1; i--){
        singleLine(size, i, i, 0);
        printf("\n");
        singleLine(size, i, i, 1);
        printf("\n");
    }
}

void smallSpiral(int size){
    int starcount = (size/4);
    // First half
    for(int i=1; i<=(starcount); i++){
        singleLine(size, i-1, i, 1);
        printf("\n");
        singleLine(size, i-1, i, 0);
        printf("\n");
    }
    // Last half
    for(int i=starcount; i>=1; i--){
        singleLine(size, i, i, 0);
        printf("\n");
        singleLine(size, i, i, 1);
        printf("\n");
    }
}

void bigSpiral(int size){
    int starcount = (size/4);
    // First half
    for(int i=1; i<=(starcount+1); i++){
        singleLine(size, i-1, i, 1);
        printf("\n");
        singleLine(size, i-1, i, 0);
        printf("\n");
    }
    // Line in middle;
    specialLine(size, starcount);
    printf("\n");
    // Last half
    for(int i=starcount; i>=1; i--){
        singleLine(size, i, i, 0);
        printf("\n");
        singleLine(size, i, i, 1);
        printf("\n");
    }
}

void singleLine(int size, int left, int right,int bw){
    drawside(left);
    int middlelength = size - nthodd(left) - nthodd(right);
    drawmid(middlelength, bw);
    drawside(right);
}

void specialLine(int size, int starcount){
    drawside(starcount+1);
    printf("*");
    drawside(starcount+1);
    
}

int nthodd(int input){
    if(input == 0){
        return 0;
    }else{
        return ((input*2)-1);
    }
}

void drawside(int input){
    if(input != 0){
        printf("*");
        for(int i=1; i<(input); i++){
            printf("-*");
        }
    }
}

void drawmid(int input, bool bw){
    // bw = 1 for star, 0 for line.
    for(int i=0; i<input; i++){
        if(bw==1){
            printf("*");
        }else{
            printf("-");
        }
    }
}
