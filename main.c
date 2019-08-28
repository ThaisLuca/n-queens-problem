
#include<stdio.h>
#include <stdbool.h>

#define N 8

void inicializeBoard(int board[N][N]);
void inicializeAux(bool slashCode[N][N], bool backslashCode[N][N]);
bool isSafe(int row, int col, int slashCode[N][N], int backslashCode[N][N], bool rowLookup[], bool slashCodeLookup[], bool backSlashCodeLookup[]);
void printSolution(int board[N][N]);


bool testSolveQueens(int board[N][N], int col, int slashCode[N][N], int backslashCode[N][N], bool rowLookup[N], bool slashCodeLookup[], bool backSlashCodeLookup[]){
	int i;

	//If all queens are placed return true
	if(col >= N) return true;

	// Try to place the queen in all rows
	for(i = 0; i < N; i++){
		
		//Check if queen can be placed on board[i][col]
		if(isSafe(i, col, slashCode, backslashCode, rowLookup, slashCodeLookup, backSlashCodeLookup)){
			//Place this queen
			board[i][col] = 1;
			rowLookup[i] = true;
			slashCodeLookup[slashCode[i][col]] = true;
			backSlashCodeLookup[backslashCode[i][col]] = true;

			// Recur to place the rest ot the queens
			if(testSolveQueens(board, col + 1, slashCode, backslashCode, rowLookup, slashCodeLookup, backSlashCodeLookup)) return true;

			//If placing queen doesn't lead to a solution, then backtrack

			board[i][col] = 0;
			rowLookup[i] = false;
			slashCodeLookup[slashCode[i][col]] = false;
			backSlashCodeLookup[backslashCode[i][col]] = false;
		}
	}

	//queen cannot be placed
	return false;
}

bool solveNQueens(){

	// Create and inicialize board
	int board[N][N];
	inicializeBoard(board);

	int slashCode[N][N];
	int backslashCode[N][N];
	bool rowLookup[N];
	rowLookup[0] = false;
	
	bool slashCodeLookup[2*N - 1];
	slashCodeLookup[0] = false;

	bool backSlashCodeLookup[2*N - 1];
	backSlashCodeLookup[0] = false;

	inicializeAux(slashCode, backslashCode);

	if(testSolveQueens(board, 0, slashCode, backslashCode, rowLookup, slashCodeLookup, backSlashCodeLookup) == false){
		printf("Solution does not exist\n");
		return false;
	} 

	//Solution found
	printSolution(board);
	return true;
}

int main (void){
	
	solveNQueens();

	return 0;
}

void inicializeBoard(int board[N][N]){
	int i, j;

	for(i=0; i < N; i++){
		for(j=0; j < N; j++){
			board[i][j] = 0;
		}
	}
}


void inicializeAux(bool slashCode[N][N], bool backslashCode[N][N]){
	int r, c;
	for(r = 0; r < N; r++){
		for(c = 0; c < N; c++){
			slashCode[r] = (r + c);
			backslashCode[r] = (r - c + 7);
		}
	}
}

void printSolution(int board[N][N]) { 
    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < N; j++) 
            printf("%2d ", board[i][j]); 
        printf("\n"); 
    } 
} 