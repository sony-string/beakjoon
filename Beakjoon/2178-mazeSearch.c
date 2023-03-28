#include <stdio.h>
#include <stdlib.h>

//queue
void pop(int *x, int *y, int **queue, int l) {
	*x = queue[l][0];
	*y = queue[l][1];
}

void push(int** queue, int x, int y, int r) {
	queue[r][0] = x;
	queue[r][1] = y;
}

int main() {
	int N, M, l = 0, r = 0;
	scanf("%d %d", &N, &M);
	int** queue = (int**)malloc(20000 * sizeof(int*));
	char** maze = (char**)malloc(N * sizeof(char*));
	//number of an element is the distance from start point. if it's zero, not visited.
	int** visited = (int**)malloc(N * sizeof(int*));
	int i, j;
	for (i = 0; i < N; i++) {
		maze[i] = (char*)malloc(M * sizeof(char));
		visited[i] = (int*)malloc(M * sizeof(int));
		for (j = 0; j < M; j++) {
			scanf(" %c", &maze[i][j]);
			visited[i][j] = 0;
		}
	}
	for (i = 0; i < 20000; i++) {
		queue[i] = (int*)malloc(2 * sizeof(int));
	}
	int x = 0, y = 0;
	push(queue, x, y, r);
	visited[y][x] = 1;
	r++;
	while (1) {
		pop(&x, &y, queue, l);
		l++;
		//printf("search in %d %d\n", x, y);
		if (x == M - 1 && y == N - 1) {
			break;
		}
		if (x > 0) {
			if (visited[y][x - 1] == 0 && maze[y][x - 1] == '1') {
				push(queue, x - 1, y, r);
				r++;
				visited[y][x - 1] = visited[y][x] + 1;
			}
		}
		if (x < M - 1) {
			if (visited[y][x + 1] == 0 && maze[y][x + 1] == '1') {
				push(queue, x + 1, y, r);
				r++;
				visited[y][x + 1] = visited[y][x] + 1;
			}
		}
		if (y < N - 1) {
			if (visited[y + 1][x] == 0 && maze[y + 1][x] == '1') {
				push(queue, x, y + 1, r);
				r++;
				visited[y + 1][x] = visited[y][x] + 1;
			}
		}
		if (y > 0) {
			if (visited[y - 1][x] == 0 && maze[y - 1][x] == '1') {
				push(queue, x, y - 1, r);
				r++;
				visited[y - 1][x] = visited[y][x] + 1;
			}
		}
	}
	printf("%d", visited[N - 1][M - 1]);

	for (i = 0; i < 20000; i++) {
		free(queue[i]);
	}
	free(queue);
	for (i = 0; i < N; i++) {
		free(maze[i]);
		free(visited[i]);
	}
	free(maze);
	free(visited);
	return 0;
}