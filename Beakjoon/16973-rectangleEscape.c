#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum {
	true, false
};

int isValidMove(int** map, int pos[], int size[], int mapSize[]) {
	if (pos[0] < 0 || size[1] < 0) {
		return false;
	}
	if (pos[0] + size[0] - 1 >= mapSize[0]) {
		return false;
	}
	if (pos[1] + size[1] - 1 >= mapSize[1]) {
		return false;
	}

	int i, row, col;
	row = pos[0] + size[0] - 1;
	col = pos[1] + size[1] - 1;
	for (i = pos[0]; i <= row; i++) {
		if (map[i][col] == 1 || map[i][pos[1]] == 1) {
			return false;
		}
	}
	for (i = pos[1]; i <= col; i++) {
		if (map[row][i] == 1 || map[pos[0]][i] == 1) {
			return false;
		}
	}
	return true;
}

int main() {
	int** queue, ** visited, ** map;
	int mapSize[2], size[2], pos[2], dst[2];
	int count = 0, endPop, row, col;
	int l = 0, r = 0;
	int i, k;
	scanf("%d %d", mapSize, mapSize + 1);
	queue = (int**)malloc(mapSize[0] * mapSize[1] * sizeof(int*));
	visited = (int**)malloc(mapSize[0] * sizeof(int*));
	map = (int**)malloc(mapSize[0] * sizeof(int*));

	for (i = 0; i < mapSize[0]; i++) {
		visited[i] = (int*)calloc(mapSize[1], sizeof(int));
		map[i] = (int*)malloc(mapSize[1] * sizeof(int));
		for (k = 0; k < mapSize[1]; k++) {
			scanf("%d", &map[i][k]);
		}
	}
	for (i = 0; i < mapSize[0] * mapSize[1]; i++) {
		queue[i] = (int*)calloc(2, sizeof(int));
	}
	scanf("%d %d %d %d %d %d", size, size + 1, pos, pos + 1, dst, dst + 1);
	pos[0]--; pos[1]--; dst[0]--; dst[1]--;
	visited[pos[0]][pos[1]] = 1;
	queue[r][0] = pos[0]; queue[r][1] = pos[1];
	r++;
	while (r > l) {
		endPop = r;
		for (; l < endPop; l++) {
			row = queue[l][0]; col = queue[l][1];
			if (row == dst[0] && col == dst[1]) {
				break;
			}
			pos[0] = row + 1;
			pos[1] = col;
			if (visited[pos[0]][pos[1]] == 0) {
				visited[pos[0]][pos[1]] = 1;
				if (isValidMove(map, pos, size, mapSize) == true) {
					queue[r][0] = pos[0]; queue[r][1] = pos[1];
					r++;
				}
			}
			pos[0] = row - 1;
			if (pos[0] >= 0) {
				if (visited[pos[0]][pos[1]] == 0) {
					visited[pos[0]][pos[1]] = 1;
					if (isValidMove(map, pos, size, mapSize) == true) {
						queue[r][0] = pos[0]; queue[r][1] = pos[1];
						r++;
					}
				}
			}
			pos[0] = row;
			pos[1] = col + 1;
			if (visited[pos[0]][pos[1]] == 0) {
				visited[pos[0]][pos[1]] = 1;
				if (isValidMove(map, pos, size, mapSize) == true) {
					queue[r][0] = pos[0]; queue[r][1] = pos[1];
					r++;
				}
			}
			pos[1] = col - 1;
			if (pos[1] >= 0) {
				if (visited[pos[0]][pos[1]] == 0) {
					visited[pos[0]][pos[1]] = 1;
					if (isValidMove(map, pos, size, mapSize) == true) {
						queue[r][0] = pos[0]; queue[r][1] = pos[1];
						r++;
					}
				}
			}
		}
		if (l != endPop) {
			break;
		}
		if (r > l) {
			count++;
		}
	}
	if (row == dst[0] && col == dst[1]) {
		printf("%d", count);
	}
	else {
		printf("-1");
	}
	return 0;
}