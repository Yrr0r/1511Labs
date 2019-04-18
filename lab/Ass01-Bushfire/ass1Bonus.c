// Bushfire assignment stage 1, 2, 3 And BONUS.
// By Hao Shi "Steve", z5191607
// Submitted on 01-03-2019
// Tut Group 2

#define MAX_N 40 // Max forest size
#define MAX_T 1000
#define MAX_WIND 100

#define WIND_NORTH 0
#define WIND_EAST 1
#define WIND_SOUTH 2
#define WIND_WEST 3
#define EMPTY 0
#define TREE 1
#define FIRE 2
#define LIGHTNING 3

// BMP Hashdefines:
#define BYTES_PER_PIXEL 3
#define BITS_PER_PIXEL (BYTES_PER_PIXEL * 8)
#define NUMBER_PLANES 1
#define PIX_PER_METRE 2835
#define MAGIC_NUMBER 0x4d42
#define NO_COMPRESSION 0
#define OFFSET 54
#define DIB_HEADER_SIZE 40
#define NUM_COLORS 0
#define CELL_SIZE 24
#define FILENAME_1 "initial.bmp"
#define FILENAME_2 "final.bmp"

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
void putFile(FILE *img, int size, int forest[][MAX_N]);
void writeData(FILE *img, int size, int forest[][MAX_N]);
void writeHeader(FILE *img, int gridsize);


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

    //Files gets open here
    FILE *initial = fopen(FILENAME_1, "w");
    FILE *final = fopen(FILENAME_2, "w");
    if(initial == NULL || final == NULL){
        fprintf(stderr, "ERROR OPEN FILES");
    }
    putFile(initial, n, forest); //First file gets done
    
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

    // Final bmp;
    putFile(final, n, forest);
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
    if(i>=0 && j>=0){
        sketchpad[i][j] = FIRE; // Make this hash defined later.
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
void putFile(FILE *img, int size, int forest[][MAX_N]){
    if(img == NULL){
        fprintf(stderr, "FATAL: ERROR OPEN FILE\n");
        return;
    }
    writeHeader(img, size);
    writeData(img, size, forest);
    fclose(img);
    return;
}

void writeData(FILE *img, int size, int forest[][MAX_N]){
    int bound = size - 1;
    // CELL_SIZE is important here.
    // Pre-defined Colors, in {B,G,R}
    // Does hashdefine accept arrays?
    unsigned char Empty[] = {0,0,0};
    unsigned char Tree[] = {0,255,0};
    unsigned char Fire[] = {0,0,255};
    unsigned char Lightning[] = {255,255,255};
    // A replicate logic of putForest
    for(int v=0; v<size; v++){
        for(int vc=0; vc<CELL_SIZE; vc++){
            for(int h=0; h<size; h++){
                for(int hc=0; hc<CELL_SIZE; hc++){
                    if(forest[bound-v][h] == EMPTY){
                        fwrite(&Empty, sizeof(char), 3, img);
                    } else if(forest[bound-v][h] == TREE){
                        fwrite(&Tree, sizeof(char), 3, img);
                    } else if(forest[bound-v][h] == FIRE){
                        fwrite(&Fire, sizeof(char), 3, img);
                    } else if(forest[bound-v][h] == LIGHTNING){
                        fwrite(&Lightning, sizeof(char), 3, img);
                    }
                }
            }
        }
    }
}

void writeHeader(FILE *file, int gridsize) {
    // at byte 0
    unsigned short magicNumber = MAGIC_NUMBER;
    fwrite(&magicNumber, sizeof magicNumber, 1, file);
    // at byte 2
    unsigned int fileSize = OFFSET + (CELL_SIZE*CELL_SIZE * gridsize*gridsize * BYTES_PER_PIXEL);
    fwrite(&fileSize, sizeof fileSize, 1, file);
    // at byte 6
    unsigned int reserved = 0;
    fwrite(&reserved, sizeof reserved, 1, file);
    // at byte 10
    unsigned int offset = OFFSET;
    fwrite(&offset, sizeof offset, 1, file);
    // at byte 14
    unsigned int dibHeaderSize = DIB_HEADER_SIZE;
    fwrite(&dibHeaderSize, sizeof dibHeaderSize, 1, file);
    // at byte 18
    unsigned int width = CELL_SIZE * gridsize;
    fwrite(&width, sizeof width, 1, file);
    // at byte 22
    unsigned int height = CELL_SIZE * gridsize;
    fwrite(&height, sizeof height, 1, file);
    // at byte 26
    unsigned short planes = NUMBER_PLANES;
    fwrite(&planes, sizeof planes, 1, file);
    // at byte 28
    unsigned short bitsPerPixel = BITS_PER_PIXEL;
    fwrite(&bitsPerPixel, sizeof bitsPerPixel, 1, file);
    // at byte 30
    unsigned int compression = NO_COMPRESSION;
    fwrite(&compression, sizeof compression, 1, file);
    // at byte 34
    unsigned int imageSize = (CELL_SIZE*CELL_SIZE * gridsize*gridsize * BYTES_PER_PIXEL);
    fwrite(&imageSize, sizeof imageSize, 1, file);
    // at byte 38
    unsigned int hResolution = PIX_PER_METRE;
    fwrite(&hResolution, sizeof hResolution, 1, file);
    // at byte 42
    unsigned int vResolution = PIX_PER_METRE;
    fwrite(&vResolution, sizeof vResolution, 1, file);
    // at byte 46
    unsigned int numColors = NUM_COLORS;
    fwrite(&numColors, sizeof numColors, 1, file);
    // at byte 50
    unsigned int importantColors = NUM_COLORS;
    fwrite(&importantColors, sizeof importantColors, 1, file);
    // Byte 54, finish
}
