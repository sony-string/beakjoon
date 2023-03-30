#include <stdio.h>
#include <stdlib.h>

//queue
void pop(int* x, int* y, int** queue, int l) {
	*x = queue[l][0];
	*y = queue[l][1];
}

void push(int** queue, int x, int y, int r) {
	queue[r][0] = x;
	queue[r][1] = y;
}

int main() {
	int numT, N, M, numCabbages, numNeeded, l = 0, r = 0;
	scanf("%d", &numT);
	int T, i, j;
	int x = 0, y = 0;
	int** visited = (int**)malloc(50 * sizeof(int*));
	int** farm = (int**)malloc(50 * sizeof(int*));
	int** queue = (int**)malloc(5000 * sizeof(int*));
	int posCabbages[2500][2];
	for (i = 0; i <50; i++) {
		farm[i] = (int*)malloc(50 * sizeof(int));
		visited[i] = (int*)malloc(50 * sizeof(int));
	}
	for (i = 0; i < 5000; i++) {
		queue[i] = (int*)malloc(2 * sizeof(int));
	}

	for (T = 0; T < numT; T++) {
		numNeeded = 0; l = 0; r = 0;
		scanf("%d %d %d", &M, &N, &numCabbages);
		for (i = 0; i < 50; i++) {
			for (j = 0; j < 50; j++) {
				farm[i][j] = 0;
				visited[i][j] = 0;
			}
		}
		for (i = 0; i < numCabbages; i++) {
			scanf("%d %d", &x, &y);
			farm[y][x] = 1;
			posCabbages[i][0] = x;
			posCabbages[i][1] = y;
		}
		for (i = 0; i < numCabbages; i++) {
			if (visited[posCabbages[i][1]][posCabbages[i][0]] == 1) {
				continue;
			}
			//printf("%d %d is searched\n",posCabbages[i][0], posCabbages[i][1]);
			numNeeded++;
			push(queue, posCabbages[i][0], posCabbages[i][1], r);
			r++;
			while (r != l) {
				pop(&x, &y, queue, l);
				l++;
				if (x > 0) {
					if (visited[y][x - 1] == 0 && farm[y][x - 1] == 1) {
						push(queue, x - 1, y, r);
						visited[y][x - 1] = 1;			
						r++;
					}
				}
				if (x < M - 1) {
					if (visited[y][x + 1] == 0 && farm[y][x + 1] == 1) {
						push(queue, x + 1, y, r);
						r++;
						visited[y][x + 1] = 1;
					}
				}
				if (y < N - 1) {
					if (visited[y + 1][x] == 0 && farm[y + 1][x] == 1) {
						push(queue, x, y + 1, r);
						visited[y + 1][x] = 1;
						r++;
					}
				}
				if (y > 0) {
					if (visited[y - 1][x] == 0 && farm[y - 1][x] == 1) {
						push(queue, x, y - 1, r);
						visited[y - 1][x] = 1;
						r++;
					}
				}
			}
		}
		printf("%d\n", numNeeded);
	}
	for (i = 0; i < 251; i++) {
		free(queue[i]);
	}
	free(queue);
	for (i = 0; i < N; i++) {
		free(farm[i]);
		free(visited[i]);
	}
	free(farm);
	free(visited);
	return 0;
}