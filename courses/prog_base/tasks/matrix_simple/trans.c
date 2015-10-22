#include <stdio.h>
#include <stdlib.h>

void fillRand(int mat[4][4]){
	int i, j, n = 4;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			mat[i][j] = rand() % 1999 - 999;
		}
	}
}
void rotateCW180(int mat[4][4]){
	int i, j, n = 4,copy[4][4];
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			copy[i][j] = mat[i][j];
		}
	}
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			mat[i][j] = copy[n-i-1][n-j-1];
		}
	}
}
void flipV(int mat[4][4]){
	int i, j, n = 4, copy[4][4];
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			copy[i][j] = mat[i][j];
		}
	}
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			mat[i][j] = copy[n - i - 1][j];
		}
	}
}
void transposSide(int mat[4][4]){
	int i, j, n = 4, copy[4][4];
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			copy[i][j] = mat[i][j];
		}
	}
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			mat[i][j] = copy[n - j - 1][n - i - 1];
		}
	}
}