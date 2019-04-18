#define MAX_N 40 // Max forest size
#define MAX_T 1000
#define MAX_WIND 100

#include <stdio.h>
#include <stdlib.h>

int sgeto(int max);
void putForest(int size, int forest[][MAX_N]);
int getWind(int windsize, int wind[][2], int windstep);
void fireProp(int size, int forest[][MAX_N],int windsize,int wind[][2],int windstep);
void plotburn(int size, int sketchpad[][MAX_N], int i,int j,int wind);
void putWindDirection(int dir);
void edgefire(int i, int j, int sketchpad[][MAX_N]);




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

    // Begin Simulation
    for(int i=0; i<=t; i++){
        printf("Time step %d:",i);
        putWindDirection(getWind(windSize,wind,i));
        putForest(n, forest);
        fireProp(n, forest, windSize, wind, i);
    }

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
    printf("\n");
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

void fireProp(int size, int forest[][MAX_N],int windsize,int wind[][2],int windstep){
    // Fire propagate
    int sketchpad[MAX_N][MAX_N] = {0}; // fire scketchpad
    // int sketchpad[size][size]; // for later prototype
    // Init sketchpad here.
    int windNow = getWind(windsize, wind, windstep);
    // Make a fire spread prototype
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(forest[i][j] == 2){
                plotburn(size, sketchpad, i,j,windNow);
            }
        }
    }
    // Let burning trees burn first
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(forest[i][j] == 2){
                forest[i][j] = 0;
            }
        }
    }
    // Now copy fire onto the unburned trees
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(sketchpad[i][j] == 2){
                if(forest[i][j] == 1){
                    forest[i][j] = 2;
                }
            }
        }
    }
}

int getWind(int windsize, int wind[][2], int windstep){
    if(windstep >= wind[windsize-1][0]){
        return wind[windsize-1][1];
    }

    int i=0; 
    while(wind[i][0] <= windstep){
        i++;
    }
    i--; // The counter will go 1 pos ahead desired position.
    return wind[i][1];
}

void plotburn(int size, int sketchpad[][MAX_N], int i,int j,int wind){
    // Functioning args: i, j, wind
    /*
    Refer to table,
    Coordinates table of (i,j):
    [-1,-1] [-1, 0] [-1, 1]
    [ 0,-1] [ 0, 0] [ 0, 1]
    [ 1,-1] [ 1, 0] [ 1, 1]
    */
    if(wind == 0){
        edgefire(i-1,j,sketchpad);
        edgefire(i-1,j-1,sketchpad);
        edgefire(i-1,j+1,sketchpad);
    } else if(wind == 2){
        edgefire(i+1,j, sketchpad);
        edgefire(i+1,j-1, sketchpad);
        edgefire(i+1,j+1, sketchpad);
    } else if(wind == 1){
        edgefire(i,j+1,sketchpad);
        edgefire(i-1,j+1,sketchpad);
        edgefire(i+1,j+1,sketchpad);
    } else if(wind == 3){
        edgefire(i,j-1,sketchpad);
        edgefire(i-1,j-1,sketchpad);
        edgefire(i+1,j-1,sketchpad);
    }
}

void putWindDirection(int dir){
    switch(dir){
        case 0: printf("WIND NORTH\n"); break;
        case 1: printf("WIND EAST\n"); break;
        case 2: printf("WIND SOUTH\n"); break;
        case 3: printf("WIND WEST\n"); break;
    }
}

void edgefire(int i, int j, int sketchpad[][MAX_N]){
    if(i>=0 && j>=0){
        sketchpad[i][j] = 2; // Make this hash defined later.
    }
}
