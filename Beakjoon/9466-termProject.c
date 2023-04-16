#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int node;
	int cycleRoot;
	int nomitation;
	int visited;
} Node;

int findCycle(Node* adjList, int* path, const int node, int* flag) {
	if (path[node] == 1) {
		adjList[node].cycleRoot = node;
		*flag = 1;
		return -1;
	}
	if (adjList[node].visited == 1) {
		return 0;
	}

	path[node] = 1;
	findCycle(adjList, path, adjList[node].nomitation, flag);
	if (adjList[adjList[node].nomitation].cycleRoot != 0 && *flag == 1) {
		adjList[node].cycleRoot = adjList[adjList[node].nomitation].cycleRoot;
	}
	if (adjList[node].cycleRoot == node) {
		*flag = 0;
	}
	path[node] = 0;
	adjList[node].visited = 1;
	return 0;
}

int main() {
	int numTestCases, numStudents, result, flag = 0;
	int i, T;
	int* path;
	Node* adjList;
	scanf("%d", &numTestCases);

	for (T = 0; T < numTestCases; T++) {
		scanf("%d", &numStudents);
		result = 0;
		adjList = (Node*)calloc(numStudents + 1, sizeof(Node));
		path = (int*)calloc(numStudents + 1, sizeof(int));
		for (i = 1; i <= numStudents; i++) {
			adjList[i].node = i;
			scanf("%d", &adjList[i].nomitation);
		}

		for (i = 1; i <= numStudents; i++) {
			flag = 0;
			findCycle(adjList, path, i, &flag);
		}

		for (i = 1; i <= numStudents; i++) {
			if (adjList[i].nomitation == i || adjList[i].cycleRoot != 0) {
				continue;
			}
			result++;
		}
		printf("%d\n", result);

		free(adjList);
		free(path);
	}

	return 0;
}