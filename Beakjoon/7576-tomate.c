#include <stdio.h>
#include <stdlib.h>

int main() {
	int l = 0, r = 0, numTomatoes = 0, numRipened = 0, count = 0, date = 0, M, N, changed = 0, numQueue;
	scanf("%d %d", &M, &N);
	int** farm = (int**)malloc(N * sizeof(int*));
	int** queue = (int**)malloc(N * M * sizeof(int*));

	int i, j;
	for (i = 0; i < N * M; i++) {
		queue[i] = (int*)malloc(2 * sizeof(int));
	}
	for (i = 0; i < N; i++) {
		farm[i] = (int*)malloc(M * sizeof(int));

		for (j = 0; j < M; j++) {
			scanf("%d", &farm[i][j]);
			if (farm[i][j] == 1) {
				numTomatoes++;
				numRipened++;
				queue[r][0] = j;
				queue[r][1] = i;
				r++;
				continue;
			}
			if (farm[i][j] == 0) {
				numTomatoes++;
				continue;
			}
			if (farm[i][j] == -1) {
				continue;
			}
		}
	}
	
	int y, x;
	while (l != r) {
		changed = 0;
		numQueue = r;
		for (; l < numQueue; l++) {
			y = queue[l][1];
			x = queue[l][0];
			if (x > 0) {
				if (farm[y][x - 1] == 0) {
					queue[r][0] = x - 1;
					queue[r][1] = y;
					r++;
					changed++;
					farm[y][x - 1] = 1;
				}
			}
			if (x < M - 1) {
				if (farm[y][x + 1] == 0) {
					queue[r][0] = x + 1;
					queue[r][1] = y;
					r++;
					changed++;
					farm[y][x + 1] = 1;
				}
			}
			if (y > 0) {
				if (farm[y - 1][x] == 0) {
					queue[r][0] = x;
					queue[r][1] = y - 1;
					r++;
					changed++;
					farm[y - 1][x] = 1;
				}
			}
			if (y < N - 1) {
				if (farm[y + 1][x] == 0) {
					queue[r][0] = x;
					queue[r][1] = y + 1;
					r++;
					changed++;
					farm[y + 1][x] = 1;
				}
			}
		}
		if (changed == 0) {
			break;
		}
		numRipened += changed;
		date++;
	}
	if (numRipened == numTomatoes) {
		printf("%d", date);
	}
	else {
		printf("-1");
	}


	for (i = 0; i < N * M; i++) {
		free(queue[i]);
	}
	free(queue);
	for (i = 0; i < N; i++) {
		farm[i] = (int*)malloc(M * sizeof(int));
	}
	free(farm);

	return 0;
}