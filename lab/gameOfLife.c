/*
 * gol.c
 *
 * Game of life in 2 dimensions
 *
 * Author:  Curtis Millar
 * Date:    8 August 2016
 *
 * This code is made freely available under the ISC licence.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define WORLD_SIZE  64
#define GENERATIONS 31
#define LIVE '*'
#define DEAD ' '

void initBuf(char *buffer);
void ptrSwap(char **a, char **b);
void iterate(char *last, char *next);
void displ(char *generation);

int main (int argc, char *argv[]) {

    char alpha[WORLD_SIZE] = {0};
    char beta[WORLD_SIZE]  = {0};

    char *last = alpha;
    char *curr = beta;

    // Initialise buffers
    initBuf(alpha);
    initBuf(beta);

    // Add life
    last[WORLD_SIZE / 2] = LIVE;
    last[(WORLD_SIZE / 2) -1] = LIVE;

    int gen;

    displ(last);
    // Iterate begin:
    for (gen = 0; ; gen++) {
        iterate(last, curr);
        displ(curr);
        ptrSwap(&last, &curr);
        usleep(1000*250);
    }


    return EXIT_SUCCESS;
}

void initBuf(char *buffer) {
    int i;

    for (i = 0; i < WORLD_SIZE; i++) {
        buffer[i] = DEAD;
    }

    return;
}

void ptrSwap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
    return;
}


void displ(char *generation) {
    int i;

    for (i = 0; i < WORLD_SIZE; i++) {
        //putc(generation[i], stdout);
        if(generation[i] == ' '){
            printf(" ");
        } else {
            printf("█");
        }
    }
    putc('\n', stdout);

    return;
}

void iterate(char *last, char *next) {
   for(int i=1; i<(WORLD_SIZE-1); i++){
       if(last[i] == DEAD){
           if(last[i-1]==LIVE || last[i+1]==LIVE){
               next[i] = LIVE;
           } else {
               next[i] = DEAD;
           }
       }
       if(last[i] == LIVE){
           if((last[i-1]==LIVE) != (last[i+1]==LIVE)){
               next[i] = LIVE;
           } else {
               next[i] = DEAD;
           }
       }
   }
}

