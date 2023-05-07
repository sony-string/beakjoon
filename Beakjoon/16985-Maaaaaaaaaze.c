#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int queue[126][3];
int visited[5][25][25];

int escape(int** cube[]) {
	int level = 0, row = 0, col = 0, pos[3];
	int l = 0, r = 0, endPop, count = -1;
	memset(visited, 0, sizeof(int[5][25][25]));
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
				pos[1] = row;
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
				pos[1] = row;
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
				pos[2] = col;
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
			}
		}
		if (l != endPop) {
			break;
		}
	}
	if (row == 4 && col == 4 && level == 4) {
		return count;
	}
	else {
		return -1;
	}
}

void rotateBoard(int** board) {
	int i, k;
	int originBoard[5][5];
	for (i = 0; i < 5; i++) {
		for (k = 0; k < 5; k++) {
			originBoard[i][k] = board[i][k];
		}
	}
	for (i = 0; i < 5; i++) {
		for (k = 0; k < 5; k++) {
			board[4 - k][i] = originBoard[i][k];
		}
	}
}

int main() {
	int*** cube = (int***)malloc(5 * sizeof(int**));
	int*** board = (int***)malloc(5 * sizeof(int**));
	int rotateCount[5] = { 0 ,0 ,0 ,0 ,0 };
	int best, temp;
	int x, y, z, a, b, i;
	for (x = 0; x < 5; x++) {
		board[x] = (int**)malloc(5 * sizeof(int*));
		for (y = 0; y < 5; y++) {
			board[x][y] = (int*)malloc(5 * sizeof(int));
			for (z = 0; z < 5; z++) {
				scanf("%d", &board[x][y][z]);
			}
		}
	}
	for (i = 0; i < 4; i++) {
		cube[i] = board[i];
	}
	best = 999;
	char* buffer = (char*)malloc(512);
	setvbuf(stdout, buffer, _IOFBF, 512);
	for (x = 0; x < 5; x++) {
		cube[0] = board[x];
		if (board[x][0][0] != 1) {
			continue;
		}
		for (y = 0; y < 5; y++) {
			if (y == x) {
				continue;
			}
			cube[1] = board[y];
			for (z = 0; z < 5; z++) {
				if (z == x || z == y) {
					continue;
				}
				cube[2] = board[z];
				for (a = 0; a < 5; a++) {
					if (a == x || a == y || a == z) {
						continue;
					}
					cube[3] = board[a];
					for (b = 0; b < 5; b++) {
						if (b == x || b == y || b == z || b == a) {
							continue;
						}
						if (board[b][4][4] != 1) {
							continue;
						}
						cube[4] = board[b];
						/*
						system("cls");
						for (int one = 0; one < 5; one++) {
							for (int two = 0; two < 5; two++) {
								for (int three = 0; three < 5; three++) {
									printf("%d ", cube[one][two][three]);
								}
								printf("\n");
							}
							printf("\n");
						}
						fflush(stdout);
						*/
						temp = escape(cube);
						if (temp != -1) {
							if (temp < best) {
								best = temp;
							}
						}
					}
				}
			}
		}
	}

	for (i = 4; i >= 0;) {
		if (rotateCount[i] == 4) {
			if (i == 0) {
				break;
			}
			rotateCount[i] = 0;
			i--;
			continue;
		}
		rotateCount[i] += 1;
		rotateBoard(board[i]);
		i = 4;

		
		for (x = 0; x < 5; x++) {
			cube[0] = board[x];
			if (board[x][0][0] != 1) {
				continue;
			}
			for (y = 0; y < 5; y++) {
				if (y == x) {
					continue;
				}
				cube[1] = board[y];
				for (z = 0; z < 5; z++) {
					if (z == x || z == y) {
						continue;
					}
					cube[2] = board[z];
					for (a = 0; a < 5; a++) {
						if (a == x || a == y || a == z) {
							continue;
						}
						cube[3] = board[a];
						for (b = 0; b < 5; b++) {
							if (b == x || b == y || b == z || b == a) {
								continue;
							}
							if (board[b][4][4] != 1) {
								continue;
							}
							cube[4] = board[b];
							/*
							system("cls");
							for (int one = 0; one < 5; one++) {
								for (int two = 0; two < 5; two++) {
									for (int three = 0; three < 5; three++) {
										printf("%d ", cube[one][two][three]);
									}
									printf("\n");
								}
								printf("\n");
							}
							fflush(stdout);
							*/
							temp = escape(cube);
							if (temp != -1) {
								if (temp < best) {
									best = temp;
								}
							}
						}
					}
				}
			}
		}
	}
	if (best != 999) {
		printf("%d", best);
	}
	else {
		printf("-1");
	}
	return 0;
}