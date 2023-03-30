#include <stdio.h>
#include <stdlib.h>

void dfs(int** matrix, int vertex, int* visited, int size) {
	if (visited[vertex] == 0) {
		visited[vertex] = 1;
		int i;
		for (i = 1; i < size; i++) {
			if (matrix[vertex][i] == 1) {
				dfs(matrix, i, visited, size);
			}
		}
	}
}

int main() {
	int** graph;
	int* visited;
	int numNodes, numEdges, count = 0;
	scanf("%d %d", &numNodes, &numEdges);
	graph = (int**)malloc((numNodes+1) * sizeof(int*));
	int i;
	for (i = 0; i < numNodes + 1; i++) {
		graph[i] = (int*)calloc(numNodes + 1, sizeof(int));
	}
	int src, dst;
	for (i = 0; i < numEdges; i++) {
		scanf("%d %d", &src, &dst);
		graph[src][dst] = 1;
		graph[dst][src] = 1;
	}
	visited = (int*)calloc(numNodes + 1, sizeof(int));
	for (i = 1; i <= numNodes; i++) {
		if (visited[i] == 0) {
			count++;
			dfs(graph, i, visited, numNodes + 1);
		}
	}
	printf("%d", count);

	for (i = 0; i <= numNodes; i++) {
		free(graph[i]);
	}
	free(graph);
	free(visited);
	return 0;
}