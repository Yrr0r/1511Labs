// Bushfire assignment stage 1, 2, 3 Not included bonus.
// By Hao Shi "Steve", z5191607
// Submitted on 01-03-2019
// Tut Group 2

#define MAX_N 40 // Max forest size
#define MAX_T 1000
#define MAX_WIND 1001

#define WIND_NORTH 0
#define WIND_EAST 1
#define WIND_SOUTH 2
#define WIND_WEST 3
#define EMPTY 0
#define TREE 1
#define FIRE 2
#define LIGHTNING 3

#include <stdio.h>
#include <stdlib.h>

int sgeto(int max);
void putForest(int size, int forest[][MAX_N]);
int getWind(int windsize, int wind[][2], int windstep);
void fireProp(int size, int forest[][MAX_N],int windsize,int wind[][2],int windstep);
void plotburn(int size, int sketchpad[][MAX_N], int i,int j,int wind);
void putWindDirection(int dir);
void edgefire(int i, int j, int sketchpad[][MAX_N]);
int countree(int size, int forest[][MAX_N]);
void lstrike(int size, int forest[][MAX_N],double lprob,int randseed);





int main(void){
    // Get T, T is steps
    int t;
    printf("Enter t: ");
    t = sgeto(MAX_T);

    // Get N, N is size of forest
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
    double lprob;
    int randseed;
    printf("Enter lightning information: \n");
    scanf("%lf %d", &lprob, &randseed);
    srand(randseed); // Init rand seq

    // Begin Simulation
    int treecount = countree(n, forest);
    
    for(int i=0; i<t; i++){
        printf("\nTime step %d:",i);
        putWindDirection(getWind(windSize,wind,i));
        if(i!=0){
            lstrike(n, forest,lprob,randseed);
        }
        putForest(n, forest);
        fireProp(n, forest, windSize, wind, i);
    }
    printf("\nTime step %d:",t);
    lstrike(n, forest,lprob,randseed);
    putWindDirection(getWind(windSize,wind,t));
    putForest(n, forest);
    printf("\n");
    // Simulation Done
    printf("Number of cells containing trees in initial forest = %d\n", treecount);
    double treeleft = treecount-countree(n,forest);
    printf("Number of cells that have burned down = %.0lf\n", treeleft);
    printf("Percentage of forest burned down = %.2lf\n ", (treeleft/treecount)*100);
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
            if(forest[i][j] == EMPTY){
                printf(". ");
            } else if(forest[i][j] == TREE) {
                printf("^ ");
            } else if(forest[i][j] == FIRE) {
                printf("* ");
            } else if(forest[i][j] == LIGHTNING){
                printf("! ");
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
            if(forest[i][j] == FIRE){
                plotburn(size, sketchpad, i,j,windNow);
            }
        }
    }
    // Let burning trees burn first
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(forest[i][j] == FIRE){
                forest[i][j] = EMPTY;
            }
        }
    }
    // Lightning trees shall light a fire now
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(forest[i][j] == LIGHTNING){
                forest[i][j] = FIRE;
            }
        }
    }
    // Now copy fire onto the unburned trees
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(sketchpad[i][j] == FIRE){
                if(forest[i][j] == TREE){
                    forest[i][j] = FIRE;
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
        case WIND_NORTH: printf("WIND NORTH\n"); break;
        case WIND_EAST: printf("WIND EAST\n"); break;
        case WIND_SOUTH: printf("WIND SOUTH\n"); break;
        case WIND_WEST: printf("WIND WEST\n"); break;
    }
}

void edgefire(int i, int j, int sketchpad[][MAX_N]){
    // This is for prevent fire go over the edge.
    // Boundary checking.
    if(i>=0 && j>=0){
        sketchpad[i][j] = FIRE; 
    }
}

int countree(int size, int forest[][MAX_N]){
    int tree = 0;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(forest[i][j] == TREE){
                tree++;
            } else if(forest[i][j] == FIRE){
                tree++;
            } else if(forest[i][j] == LIGHTNING){
                tree++;
            }
        }
    }
    return tree;
}

void lstrike(int size, int forest[][MAX_N],double lprob,int randseed){
    if(lprob == 0){
        return;
    }
    double randnum = rand();
    if(randnum/RAND_MAX <= lprob){
        int randnum2 = rand();
        randnum2 = randnum2%(size*size);
        if(forest[randnum2/size][randnum2%size] == TREE){
            forest[randnum2/size][randnum2%size] = LIGHTNING;
        }
    }
}
