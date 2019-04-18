// unfinished yet

#include <stdio.h>

#define SIZE 3
#define NOUGHT 1
#define CROSS 2
#define NO_WINNER 0
#define DRAW 100

void readBoard(int board[SIZE][SIZE]);
void printBoard(int board[SIZE][SIZE]);
int winner(int board[SIZE][SIZE]);

int main(void) {
    int i, j;
    int board[SIZE][SIZE];
    // Read Board:
    readBoard(board);
    printBoard(board);
    // I just used switch here.
    switch(winner(board)){
        case(CROSS): printf("Crosses Win\n");break;
        case(NOUGHT): printf("Noughts Win\n");break;
        case(NO_WINNER): printf("There are no winners\n");break;
        case(DRAW): printf("It is a draw\n");break;
    }
    
    return 0;
}

void readBoard(int board[SIZE][SIZE]){
    int size = SIZE;
    printf("Please enter the board: \n");
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            scanf("%d", &board[i][j]);
        }
    }
}
void printBoard(int board[SIZE][SIZE]){
    int size = SIZE;
    printf("Here is the board: \n \n");
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if((board[i][j]) == 0){
                printf("O ");
            } else if(board[i][j] == 1){
                printf("X ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int winner(int board[SIZE][SIZE]){
    // RETURN 1 for o, 2 for x, 0 for no_winner, 100 for draw.
    int size = SIZE;
    
    int count = 0;
    // In direction of demension 1
    for(int r=0; r<size; r++){
        for(int p=0; p<size; p++){
            if(board[r][p] != 2){
                count = count + board[r][p];
            } else {
                count = -10*size;
            }
        }
        // sum o = 0, sum x = 3
        if(count == 0){
            return NOUGHT;
        } else if(count == size){
            return CROSS;
        }
        count = 0;
    }
    // In direction of demension 2
    for(int c=0; c<size; c++){
        for(int p=0; p<size; p++){
            if(board[p][c] != 2){
                count = count + board[p][c];
            } else {
                count = -10*size;
            }
        }
        // sum o = 0, sum x = 3
        if(count == 0){
            return NOUGHT;
        } else if(count == size){
            return CROSS;
        }
        count = 0;
    }
    // In direction of diagonals (0,0) to (1,1)
    for(int i=0; i<size; i++){
        if(board[i][i] != 2){
            count = count + board[i][i];
        } else {
            count = -10*size;
        }
    }
    // sum o = 0, sum x = 3
    if(count == 0){
        return NOUGHT;
    } else if(count == size){
        return CROSS;
    }
    count = 0;
    
    // In direction of diagonals (0,1) to (1,0)
    for(int i=0; i<size; i++){
        if(board[i][(size-1)-i] != 2){
            count = count + board[i][(size-1)-i];
        } else {
            count = -10*size;
        }
    }
    // sum o = 0, sum x = 3
    if(count == 0){
        return NOUGHT;
    } else if(count == size){
        return CROSS;
    }
    count = 0;
        
    // Draw test
    int empty = 0;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(board[i][j] == 2){
                empty ++;
            }
        }
    }
    if(empty == 0){
        return DRAW;
    } else {
        return NO_WINNER;
    }
}
/*
 * 00 01 02
 * 10 11 12
 * 20 21 22
 */
