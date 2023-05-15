#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
	blank = 0, knight, queen, pawn
};

int size[2];
int queenmov[8][2] = { {0, 1}, {1, 1}, {1, 0}, {1, -1}, { 0, -1}, {-1, -1}, {-1, 0}, {-1, 1} };
int knightmov[8][2] = { {2, 1}, {2, -1}, {-2, -1}, {-2, 1}, {1, -2}, {-1, -2}, {1, 2}, {-1, 2} };

void queenCheck(int** board, char** mask, int pos[]) {
	int now[2];
	mask[pos[0]][pos[1]] = 1;
	for (int i = 0; i < 8; i++) {
		now[0] = pos[0] + queenmov[i][0];
		now[1] = pos[1] + queenmov[i][1];
		while (0 <= now[0] && now[0] < size[0] && 0 <= now[1] && now[1] < size[1]) {
			if (board[now[0]][now[1]] != blank) {
				break;
			}
			mask[now[0]][now[1]] = 1;
			now[0] += queenmov[i][0];
			now[1] += queenmov[i][1];
		}
	}
}

void knightCheck(char** mask, int pos[]) {
	int next[2];
	mask[pos[0]][pos[1]] = 1;
	for (int i = 0; i < 8; i++) {
		next[0] = pos[0] + knightmov[i][0];
		next[1] = pos[1] + knightmov[i][1];
		if (0 <= next[0] && next[0] < size[0] && 0 <= next[1] && next[1] < size[1]) {
			mask[next[0]][next[1]] = 1;
		}
	}
}

int main() {
	int** board;
	char** mask;
	
	int pos[2];
	int typeEnum[3] = { queen, knight, pawn };
	int type;
	int numPieces;
	int count = 0;
	
	scanf("%d %d", size, size + 1);
	board = (int**)malloc(size[0] * sizeof(int*));
	mask = (char**)malloc(size[0] * sizeof(char*));
	for (int i = 0; i < size[0]; i++) {
		board[i] = (int*)calloc(size[1], sizeof(int));
		mask[i] = (char*)calloc(size[1], 1);
	}

	for (int i = 0; i < 3; i++) {
		scanf("%d", &numPieces);
		type = typeEnum[i];
		for (int k = 0; k < numPieces; k++) {
			scanf("%d %d", pos, pos + 1);
			pos[0]--;
			pos[1]--;
			board[pos[0]][pos[1]] = type;
		}
	}

	for (int row = 0; row < size[0]; row++) {
		for (int col = 0; col < size[1]; col++) {
			type = board[row][col];
			pos[0] = row;
			pos[1] = col;
			if (type == blank) {
				continue;
			}
			else if (type == queen) {
				queenCheck(board, mask, pos);
				continue;
			}
			else if (type == knight) {
				knightCheck(mask, pos);
				continue;
			}
			else {
				mask[row][col] = 1;
				continue;
			}
		}
	}

	count = 0;
	for (int row = 0; row < size[0]; row++) {
		for (int col = 0; col < size[1]; col++) {
			if (mask[row][col] == 0) {
				count++;
				continue;
			}
		}
	}
	printf("%d", count);
	return 0;
}