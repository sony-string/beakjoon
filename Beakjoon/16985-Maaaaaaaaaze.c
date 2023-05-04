#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int queue[126][3];
int visited[5][25][25];

int escape(int** cube[]) {
	int level = 0, row = 0, col = 0, pos[3];
	int l = 0, r = 0, endPop, count = -1;
	memset(visited, 0, sizeof(int[5][25][25]));
	int i;
	queue[r][0] = level; queue[r][1] = row; queue[r][2] = col;
	visited[0][0][0] = 1;
	r++;
	while (l < r) {
		count++;
		endPop = r;
		for (; l < endPop; l++) {
			level = queue[l][0]; row = queue[l][1]; col = queue[l][2];
			if (level == 4 && row == 4 && col == 4) {
				break;
			}
			l++;
			pos[0] = level; pos[1] = row; pos[2] = col;
			if (level > 0) {
				pos[0] -= 1;
				if (visited[pos[0]][pos[1]][pos[2]] == 0) {
					visited[pos[0]][pos[1]][pos[2]] = 1;
					if (cube[pos[0]][pos[1]][pos[2]] == 1) {
						queue[r][0] = pos[0]; queue[r][1] = pos[1]; queue[r][2] = pos[2];
						r++;
					}
				}
				pos[0] = level;
			}
			if (level < 4) {
				pos[0] += 1;
				if (visited[pos[0]][pos[1]][pos[2]] == 0) {
					visited[pos[0]][pos[1]][pos[2]] = 1;
					if (cube[pos[0]][pos[1]][pos[2]] == 1) {
						queue[r][0] = pos[0]; queue[r][1] = pos[1]; queue[r][2] = pos[2];
						r++;
					}
				}
				pos[0] = level;
			}
			if (row > 0) {
				pos[1] -= 1;
				if (visited[pos[0]][pos[1]][pos[2]] == 0) {
					visited[pos[0]][pos[1]][pos[2]] = 1;
					if (cube[pos[0]][pos[1]][pos[2]] == 1) {
						queue[r][0] = pos[0]; queue[r][1] = pos[1]; queue[r][2] = pos[2];
						r++;
					}
				}
				pos[1] = level;
			}
			if (row < 4) {
				pos[1] += 1;
				if (visited[pos[0]][pos[1]][pos[2]] == 0) {
					visited[pos[0]][pos[1]][pos[2]] = 1;
					if (cube[pos[0]][pos[1]][pos[2]] == 1) {
						queue[r][0] = pos[0]; queue[r][1] = pos[1]; queue[r][2] = pos[2];
						r++;
					}
				}
				pos[1] = level;
			}
			if (col > 0) {
				pos[2] -= 1;
				if (visited[pos[0]][pos[1]][pos[2]] == 0) {
					visited[pos[0]][pos[1]][pos[2]] = 1;
					if (cube[pos[0]][pos[1]][pos[2]] == 1) {
						queue[r][0] = pos[0]; queue[r][1] = pos[1]; queue[r][2] = pos[2];
						r++;
					}
				}
				pos[2] = level;
			}
			if (col < 4) {
				pos[2] += 1;
				if (visited[pos[0]][pos[1]][pos[2]] == 0) {
					visited[pos[0]][pos[1]][pos[2]] = 1;
					if (cube[pos[0]][pos[1]][pos[2]] == 1) {
						queue[r][0] = pos[0]; queue[r][1] = pos[1]; queue[r][2] = pos[2];
						r++;
					}
				}
				pos[2] = level;
			}
		}
		if (l != endPop) {
			break;
		}
	}
	if (row == 4 && col == 4 && row == 4) {
		return count;
	}
	else {
		return -1;
	}
}

void rotateBoard(int dst[][5], int src[][5]) {
	int i, k;
	for (i = 0; i < 5; i++) {
		for (k = 0; k < 5; k++) {
			dst[4 - k][i] = src[i][k];
		}
	}
}

int main() {
	int** cube[5];
	int board[5][5][5];
	int originBoard[5][5][5];
	int rotateCount[5] = { 0 ,0 ,0 ,0 ,0 };
	int best, temp;
	int x, y, z, a, b, i;
	for (x = 0; x < 5; x++) {
		for (y = 0; y < 5; y++) {
			for (z = 0; z < 5; z++) {
				scanf("%d", &originBoard[x][y][z]);
			}
		}
	}
}