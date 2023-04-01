#include <stdio.h>
#include <stdlib.h>

int solveN_Queen(int x, int y, int N, char **board) {
	if (y == N - 1) {
		return 1;
	}
	int count = 0, i, j;
	int depth = N - y;
	char** newBoard = (char**)malloc(depth * sizeof(char*));
	int temp = 0;
	for (i = 0; i < depth; i++) {
		newBoard[i] = (char*)malloc(N * sizeof(char));
		for (j = 0; j < N; j++) {
			temp++;
			newBoard[i][j] = board[i + 1][j];
		}
	}
	int xx = x, yy = 0;
	while (xx < N && yy < depth) {
		newBoard[yy][xx] = 1;
		yy++; xx++;
	}
	xx = x; yy = 0;
	while (xx >= 0 && yy < depth) {
		newBoard[yy][xx] = 1;
		yy++; xx--;
	}
	xx = x; yy = 0;
	while (yy < depth) {
		newBoard[yy][xx] = 1;
		yy++;
	}
	for (i = 0; i < N; i++) {
		if (newBoard[1][i] == 0) {
			count += solveN_Queen(i, y+1, N, newBoard);
		}
	}
	for (i = 0; i < depth; i++) {
		free(newBoard[i]);
	}
	free(newBoard);
	return count;
}

int main() {
	int nQueen, count = 0;
	char **board;
	scanf("%d", &nQueen);
	board = (char**)malloc((nQueen + 1) * sizeof(char*));
	int x, y;
	for (y = 0; y < nQueen + 1; y++) {
		board[y] = (char*)malloc(nQueen * sizeof(char));
		for (x = 0; x < nQueen; x++) {
			board[y][x] = 0;
		}
	}
	for (x = 0; x < nQueen/2; x++) {
		count += 2 * solveN_Queen(x, 0, nQueen, board);
		//printf("%d\n",count);
	}
	if (nQueen % 2 == 1) {
		count += solveN_Queen(x, 0, nQueen, board);
	}
	free(board);
	printf("%d", count);
	return 0;
}