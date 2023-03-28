#include <stdio.h>
#include <stdlib.h>

int dfs(int** matrix, int vertex, int *visited, int size) {
	int count = 0;
	if (visited[vertex] == 1) {
		return 0;
	}
	else {
		count++;
		visited[vertex] = 1;
		int i;
		for (i = 0; i < size; i++) {
			if (matrix[vertex][i] == 1) {
				count += dfs(matrix, i, visited, size);
			}
		}
		return count;
	}
}

int main() {
	int numComputers, numEdges, i, j, src, dst;
	scanf("%d", &numComputers);
	scanf("%d", &numEdges);
	numComputers++;
	int** adjMatrix = (int**)malloc(numComputers * sizeof(int*));
	int* visited = (int*)malloc(numComputers * sizeof(int));
	for (i = 0; i < numComputers; i++) {
		visited[i] = 0;
		adjMatrix[i] = (int*)malloc(numComputers * sizeof(int));
		for (j = 0; j < numComputers; j++) {
			adjMatrix[i][j] = 0;
		}
	}
	for (i = 0; i < numEdges; i++) {
		scanf("%d %d", &src, &dst);
		adjMatrix[src][dst] = 1;
		adjMatrix[dst][src] = 1;
	}
	printf("%d", dfs(adjMatrix, 1, visited, numComputers)-1);
	free(visited);
	for (i = 0; i < numComputers; i++) {
		free(adjMatrix[i]);
	}
	free(adjMatrix);
	return 0;
}