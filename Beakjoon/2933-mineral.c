#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int coloring(int** visited, char** map, int pos[], int size[]) {
	int** stack = (int**)malloc(size[0] * size[1] * sizeof(int*));
	visited[pos[0]][pos[1]] = 1;
	int count = 0, i, row = pos[0], col = pos[1], top = 0;
	for (i = 0; i < size[0] * size[1]; i++) {
		stack[i] = (int*)calloc(3, sizeof(int*));
	}
	stack[top][0] = pos[0]; stack[top][1] = pos[1]; stack[top][2] = 0;
	top++;
	while (top != 0) {
		top--;
		row = stack[top][0]; col = stack[top][1]; i = stack[top][2];
		while (1) {
			visited[row][col] = 1;
			count++;
			for (; i < 4; i++) {
				if (i == 0 && row > 0) {
					if (map[row - 1][col] == 'x' && visited[row - 1][col] == 0) {
						stack[top][0] = row;
						stack[top][1] = col;
						stack[top][2] = i + 1;
						top++;
						row = row - 1;
						i = 0;
						break;
					}
				}
				else if (i == 1 && col < size[1] - 1) {
					if (map[row][col + 1] == 'x' && visited[row][col + 1] == 0) {
						stack[top][0] = row;
						stack[top][1] = col;
						stack[top][2] = i + 1;
						top++;
						col = col + 1;
						i = 0;
						break;
					}
				}
				else if (i == 2 && row < size[0] - 1) {
					if (map[row + 1][col] == 'x' && visited[row + 1][col] == 0) {
						stack[top][0] = row;
						stack[top][1] = col;
						stack[top][2] = i + 1;
						top++;
						row = row + 1;
						i = 0;
						break;
					}
				}
				else if (i == 3 && col > 0) {
					if (map[row][col - 1] == 'x' && visited[row][col - 1] == 0) {
						stack[top][0] = row;
						stack[top][1] = col;
						stack[top][2] = i + 1;
						top++;
						col = col - 1;
						i = 0;
						break;
					}
				}
			}
			if (i == 4) {
				break;
			}
		}
	}
	return count;
}

int fallCluster(char** map, int** cluster, int size[]) {
	int* bottom = (int*)calloc(size[1], sizeof(int));
	int height = 999, index = 5;
	int i, k;
	for (k = 0; k < size[1]; k++) {
		for (i = size[0] - 1; i >= 0; i--) {
			if (cluster[i][k] != 0) {
				bottom[k] = i;
				break;
			}
		}
	}
	for (k = 0; k < size[1]; k++) {
		if (bottom[k] == 0) {
			continue;
		}
		for (i = bottom[k] + 1; i < size[0]; i++) {
			if (map[i][k] == 'x') {
				break;
			}
		}
		if (i - bottom[k] < height) {
			height = i - bottom[k];
		}
	}
	for (i = size[0] - height; i >= 0; i--) {
		for (k = 0; k < size[1]; k++) {
			if (cluster[i][k] == 1) {
				cluster[i][k] = 0;
				map[i][k] = '.';
				map[i + height - 1][k] = 'x';
			}
		}
	}
	free(bottom);
	return index;
}

int checkCluster(char** map, int pos[], int size[]) {
	int** visited = (int**)calloc(size[0], sizeof(int*));
	int i, k, next[2], isFalling;
	for (i = 0; i < size[0]; i++) {
		visited[i] = (int*)calloc(size[1], sizeof(int));
	}
	if (pos[0] > 0 && map[pos[0] - 1][pos[1]] == 'x') {
		visited[pos[0] - 1][pos[1]] = 1;
		next[0] = pos[0] - 1; next[1] = pos[1];
		coloring(visited, map, next, size);

		isFalling = 1;
		for (k = 0; k < size[1]; k++) {
			if (visited[size[0] - 1][k] == 1) {
				isFalling = 0;
				break;
			}
		}
		if (isFalling == 1) {
			fallCluster(map, visited, size);
			for (i = 0; i < size[0]; i++) {
				free(visited[i]);
			}
			free(visited);
			return 1;
		}
	}

	if (pos[0] < size[0] - 1 && map[pos[0] + 1][pos[1]] == 'x') {
		for (i = 0; i < size[0]; i++) {
			memset(visited[i], 0, size[1] * sizeof(int));
		}
		next[0] = pos[0] + 1; next[1] = pos[1];
		coloring(visited, map, next, size);
		isFalling = 1;
		for (k = 0; k < size[1]; k++) {
			if (visited[size[0] - 1][k] == 1) {
				isFalling = 0;
				break;
			}
		}
		if (isFalling == 1) {
			fallCluster(map, visited, size);
			for (i = 0; i < size[0]; i++) {
				free(visited[i]);
			}
			free(visited);
			return 1;
		}
	}

	if (pos[1] > 0 && map[pos[0]][pos[1] - 1] == 'x') {
		for (i = 0; i < size[0]; i++) {
			memset(visited[i], 0, size[1] * sizeof(int));
		}
		next[0] = pos[0]; next[1] = pos[1] - 1;
		coloring(visited, map, next, size);

		isFalling = 1;
		for (k = 0; k < size[1]; k++) {
			if (visited[size[0] - 1][k] == 1) {
				isFalling = 0;
				break;
			}
		}
		if (isFalling == 1) {
			fallCluster(map, visited, size);
			for (i = 0; i < size[0]; i++) {
				free(visited[i]);
			}
			free(visited);
			return 1;
		}
	}

	if (pos[1] < size[1] - 1 && map[pos[0]][pos[1] + 1] == 'x') {
		for (i = 0; i < size[0]; i++) {
			memset(visited[i], 0, size[1] * sizeof(int));
		}
		next[0] = pos[0]; next[1] = pos[1] + 1;
		coloring(visited, map, next, size);

		isFalling = 1;
		for (k = 0; k < size[1]; k++) {
			if (visited[size[0] - 1][k] == 1) {
				isFalling = 0;
				break;
			}
		}
		if (isFalling == 1) {
			fallCluster(map, visited, size);
			for (i = 0; i < size[0]; i++) {
				free(visited[i]);
			}
			free(visited);
			return 1;
		}
	}
	for (i = 0; i < size[0]; i++) {
		free(visited[i]);
	}
	free(visited);
	return 0;
}

int main() {
	int size[2], pos[2], numThrow, level, direction;
	char** map;
	scanf("%d %d", size, size + 1);
	int i, k;
	map = (char**)malloc(size[0] * sizeof(char*));
	for (i = 0; i < size[0]; i++) {
		map[i] = (char*)malloc(size[1] + 1);
		scanf("%s", map[i]);
	}

	scanf("%d", &numThrow);
	for (i = 0; i < numThrow; i++) {
		scanf("%d", &level);
		level = size[0] - level;
		pos[0] = level;
		pos[1] = 999;
		if (i % 2 == 0) {
			k = 0;
			direction = 1;
		}
		else {
			k = size[1] - 1;
			direction = -1;
		}
		for (; 0 <= k && k < size[1]; k += direction) {
			if (map[level][k] == 'x') {
				pos[1] = k;
				map[level][k] = '.';
				break;
			}
		}
		if (pos[1] != 999) {
			checkCluster(map, pos, size);
		}
		/*
		printf("************\n");
		for (k = 0; k < size[0]; k++) {
			printf("%s\n", map[k]);
		}
		*/
	}
	for (i = 0; i < size[0]; i++) {
		printf("%s", map[i]);
		if (i != size[0] - 1) {
			printf("\n");
		}
	}

	return 0;
}