#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char** map;
	int** dist;
	int size[2];
	int result = 0, mov, flag = 0;
	scanf("%d %d", size, size + 1);
	map = (char**)malloc(size[0] * sizeof(char*));
	dist = (int**)malloc(size[0] * sizeof(int*));
	int i, j, t;
	for (i = 0; i < size[0]; i++) {
		dist[i] = (int*)calloc(size[1], sizeof(int));
		map[i] = (char*)malloc((size[1] + 1));
		scanf("%s", map[i]);
	}
	mov = map[0][0] - '0';
	if (mov < size[0]) {
		dist[mov][0] = -1;
		flag = 1;
	}
	if (mov < size[1]) {
		dist[0][mov] = -1;
		flag = 1;
	}
	if (flag == 0) {
		printf("1");
		return 0;
	}
	for (t = 0; t < size[0] * size[1] + 1; t++) {
		for (i = 0; i < size[0]; i++) {
			for (j = 0; j < size[1]; j++) {
				if (map[i][j] == 'H' || dist[i][j] == 0) {
					continue;
				}
				mov = map[i][j] - '0';
				if (i + mov < size[0]) {
					if (dist[i + mov][j] > dist[i][j] - 1) {
						dist[i + mov][j] = dist[i][j] - 1;
					}
				}
				if (j + mov < size[1]) {
					if (dist[i][j + mov] > dist[i][j] - 1) {
						dist[i][j + mov] = dist[i][j] - 1;
					}
				}
				if (i - mov >= 0) {
					if (dist[i - mov][j] > dist[i][j] - 1) {
						dist[i - mov][j] = dist[i][j] - 1;
					}
				}
				if (j - mov >= 0) {
					if (dist[i][j - mov] > dist[i][j] - 1) {
						dist[i][j - mov] = dist[i][j] - 1;
					}
				}
			}
		}
	}
	for (i = 0; i < size[0]; i++) {
		for (j = 0; j < size[1]; j++) {
			if (dist[i][j] != 0) {
				if (map[i][j] != 'H') {
					if (dist[i][j] - 1 < result) {
						result = dist[i][j] - 1;
					}
				}
				else if (dist[i][j] < result) {
					result = dist[i][j];
				}
			}
			if (map[i][j] == 'H' || dist[i][j] == 0) {
				continue;
			}
			mov = map[i][j] - '0';
			if (i + mov < size[0]) {
				if (dist[i + mov][j] > dist[i][j] - 1) {
					result = 1;
					break;
				}
			}
			if (j + mov < size[1]) {
				if (dist[i][j + mov] > dist[i][j] - 1) {
					result = 1;
					break;
				}
			}
			if (i - mov >= 0) {
				if (dist[i - mov][j] > dist[i][j] - 1) {
					result = 1;
					break;
				}
			}
			if (j - mov >= 0) {
				if (dist[i][j - mov] > dist[i][j] - 1) {
					result = 1;
					break;
				}
			}
		}
		if (j != size[1]) {
			break;
		}
	}
	printf("%d", -1 * result);
	return 0;
}