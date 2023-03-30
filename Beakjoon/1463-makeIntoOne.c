#include <stdio.h>
#include <stdlib.h>

int main() {
	int* queue, *visited;
	int num, count = -1, l = 0, r = 0, endPop;
	scanf("%d", &num);
	queue = (int*)malloc(num * sizeof(int));
	visited = (int*)calloc(num + 1, sizeof(int));
	queue[r] = num;
	r++;
	while (l != r) {
		count++;
		//printf("count : %d\n", count);
		endPop = r;
		for (; l < endPop; l++) {
			//printf("%d is searching\n", queue[l]);
			if (queue[l] == 1) {
				break;
			}
			if (queue[l] % 3 == 0) {
				if (visited[queue[l] / 3] == 0) {
					visited[queue[l] / 3] = 1;
					queue[r] = queue[l] / 3;
					r++;
				}
			}
			if (queue[l] % 2 == 0) {
				if (visited[queue[l] / 2] == 0) {
					visited[queue[l] / 2] = 1;
					queue[r] = queue[l] / 2;
					r++;
				}
			}
			if (visited[queue[l] - 1] == 0) {
				queue[r] = queue[l] - 1;
				visited[queue[l] - 1] = 1;
				queue[r] = queue[l] - 1;
				r++;
			}
		}
		if (l != endPop) {
			break;
		}
	}
	printf("%d", count);
	
	free(visited);
	free(queue);
	return 0;
}