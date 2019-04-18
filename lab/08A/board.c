#include <stdio.h>
#include <stdlib.h>

#define SIZE 4

struct piece {
	char color; // "RBYG"
	char symbol; // "*^#$"
};
typedef struct piece Piece;

int areEqual(Piece p1, Piece p2); // Return 0 for different, 1 for equal.
void printPiece(Piece p);
int readPiece(Piece *p);
int main(void){
	Piece board[SIZE][SIZE];
	printf("Enter pieces: ");
	
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			readPiece(&board[i][j]);
			if(!(i==SIZE-1&&j==SIZE-1)){
				getchar();
			}
		}
	}
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			printPiece(board[i][j]);
			if(!(i==SIZE-1&&j==SIZE-1)){
				printf(" ");
			}
		}
		printf("\n");
	}
}

int readPiece(Piece *p){
	scanf("%c%c", &p->color, &p->symbol);
	switch(p->color){
		case 'R': break;
		case 'B': break;
		case 'Y': break;
		case 'G': break;
		default: return (0); break;
	}
	switch(p->symbol){
		case '*': break;
		case '^': break;
		case '#': break;
		case '$': break;
		default: return (0); break;
	}
	return 1; // This for illegal input
}

void printPiece(Piece p){
	printf("%c", p.color);
	printf("/");
	printf("%c", p.symbol);
}

int areEqual(Piece p1, Piece p2){
	// 0 for different, 1 for equal.
	if(p1.color != p2.color){
		return 0;
	}
	if(p1.symbol != p2.symbol){
		return 0;
	}
	return 1;
}

