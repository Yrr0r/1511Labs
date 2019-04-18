#include <stdio.h>

#define SIZE 3

void readBoard(int board[SIZE][SIZE]);
void printBoard(int board[SIZE][SIZE]);

int main(void) {
    int i, j;
    int board[SIZE][SIZE];
    // Read Board:
    readBoard(board);
    printBoard(board);
    
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
