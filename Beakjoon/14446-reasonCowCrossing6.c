#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
	right = 0, left = 1, down = 2, up = 3
};

int mov[4][2] = { {1, 0}, {0, -1}, {0, 1}, {-1, 0} };
int dir[4] = { down, left, right, up };
int size;


void dfs(int** map, int*** road, int pos[], int color) {
	map[pos[0]][pos[1]] = color;
	int next[2];
	for (int i = 0; i < 4; i++) {
		next[0] = pos[0] + mov[dir[i]][0];
		next[1] = pos[1] + mov[dir[i]][1];
		if (next[0] < 0 || next[0] >= size || next[1] < 0 || next[1] >= size) {
			continue;
		}
		else if (map[next[0]][next[1]] == color) {
			continue;
		}
		else if (road[pos[0]][pos[1]][dir[i]] == 1) {
			continue;
		}
		dfs(map, road, next, color);
	}
}


int main() {
	int** map;
	int** cowMap;
	int*** road;
	int* areaDegree;
	
	int numCows, numRoads, numAreas;
	int sum;
	int direction;
	int pos[2];
	int src[2];
	int dst[2];
	scanf("%d %d %d", &size, &numCows, &numRoads);
	
	numAreas = 0;
	map = (int**)malloc(size * sizeof(int*));
	cowMap = (int**)malloc(size * sizeof(int*));
	road = (int***)malloc(size * sizeof(int**));

	for (int i = 0; i < size; i++) {
		map[i] = (int*)calloc(size, sizeof(int));
		cowMap[i] = (int*)calloc(size, sizeof(int));
		road[i] = (int**)malloc(size * sizeof(int*));
		for (int k = 0; k < size; k++) {
			road[i][k] = (int*)calloc(4, sizeof(int));
		}
	}

	for (int i = 0; i < numRoads; i++) {
		scanf("%d %d %d %d", src, src + 1, dst, dst + 1);
		src[0]--; src[1]--; dst[0]--; dst[1]--;
		direction = 0;
		for (int i = 0; i < 4; i++) {
			if (src[0] + mov[i][0] == dst[0] && src[1] + mov[i][1] == dst[1]) {
				direction = i;
				break;;
			}
		}
		road[src[0]][src[1]][direction] = 1;
		road[dst[0]][dst[1]][3 - direction] = 1;
	}

	for (int i = 0; i < numCows; i++) {
		scanf("%d %d", pos, pos + 1);
		pos[0]--; pos[1]--;
		cowMap[pos[0]][pos[1]] = 1;
	}

	for (int i = 0; i < size; i++) {
		for (int k = 0; k < size; k++) {
			if (map[i][k] == 0) {
				numAreas++;
				pos[0] = i; pos[1] = k;
				dfs(map, road, pos, numAreas);
			}
		}
	}
	areaDegree = (int*)calloc(numAreas + 1, sizeof(int));
	for (int i = 0; i < size; i++) {
		for (int k = 0; k < size; k++) {
			if (cowMap[i][k] == 1) {
				areaDegree[map[i][k]]++;
			}
		}
	}
	sum = 0;
	for (int i = 1; i < numAreas; i++) {
		for (int k = i + 1; k <= numAreas; k++) {
			sum += areaDegree[i] * areaDegree[k];
		}
	}
	printf("%d", sum);
	return 0;
}