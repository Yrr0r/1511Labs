#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if(argc != 5){puts("WRONG ARGS");exit(0);}
    double lprob = atof(argv[1]);
    int randseed = atoi(argv[2]);
    int steps = atoi(argv[3]);
    int size = atoi(argv[4]);
    
    srand(randseed);
    
    for(int i=0; i<steps; i++){
        printf("%d STEP\n", i+1);
        double randnum = rand();
        printf("    RANDNUM : %.0lf\n", randnum);
        if(randnum/RAND_MAX <= lprob){
            printf("    PROB : %lf\n", randnum/RAND_MAX);
            int randnum2 = rand();
            printf("    RANDNUM 2 : %d\n", randnum2);
            randnum2 = randnum2%(size*size);
            printf("    Lightning Pos: %d, %d \n", randnum2%size, randnum2/size);
        }
    }
}
