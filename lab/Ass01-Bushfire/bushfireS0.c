#define MAX_N 40 // Max forest size
#define MAX_T 1000
#define MAX_WIND 100

#include <stdio.h>
#include <stdlib.h>

int sgeto(int max);
void putForest(int size, int forest[][MAX_N]);

int main(void){
    // Get T
    int t;
    printf("Enter t: ");
    t = sgeto(MAX_T);

    // Get N
    int n;
    printf("Enter n: ");
    n = sgeto(MAX_N);

    // Scan forest
    int forest[MAX_N][MAX_N];
    printf("Enter %d by %d forest: \n", n,n);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf("%d", &forest[i][j]);
        }
    }

    // Scan wind size:
    int windSize;
    printf("Enter wind information size: ");
    windSize = sgeto(MAX_WIND);

    // Scan wind data:
    int wind[MAX_WIND][2];
    printf("Enter wind direction information: \n");
    for(int i=0; i<windSize; i++){
        for(int j=0; j<2; j++){
            scanf("%d", &wind[i][j]);
        }
    }
    
    // Scan lightning info:
    double lightning[2];
    printf("Enter lightning information: \n");
    scanf("%lf %lf", &lightning[0],&lightning[1]);

    // Disp Forest:
    putForest(n , forest);

}

int sgeto(int max){
    // One sided safe get
    int i;
    if(scanf("%d",&i) != 1 || i<0 || i>max){
        printf("Incorrect Input: n must be 0 .. %d \n", MAX_N);
        exit(1);
    }
    return i;
}

void putForest(int size , int forest[][MAX_N]){ 
    //Can i variable its column? make MAX_N into 'size' ?
    // Also, how to print varia amount of abcdef?
    printf("      ");
    for(int i=0; i<size; i++){
        printf("%c ", ('a'+i));
    }
    printf("    ");
    for(int i=0; i<(size+2); i++){
        printf("# ");
    }
    printf("\n");
    for(int i=0; i<size; i++){
        printf("%2d  # ", i);
        for(int j=0; j<size; j++){
            if(forest[i][j] == 0){
                printf(". ");
            } else if(forest[i][j] == 1) {
                printf("^ ");
            } else if(forest[i][j] == 2) {
                printf("* ");
            }
        }
        printf("#\n");
    }
    printf("    ");
    for(int i=0; i<(size+2); i++){
        printf("# ");
    }
    printf("\n");

    return;
}
