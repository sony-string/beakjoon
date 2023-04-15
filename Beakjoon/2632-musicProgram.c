#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int node;
	int isRoot;
	struct Node* nextNode;
	struct Node* lastNode;
} Node;

int getArray(int* arr, int* isAppeared, int* numAppeared, const Node* adjList, int node) {
	if (isAppeared[node] == 1) {
		return 0;
	}
	isAppeared[node] = 1;
	const Node* nodep = adjList[node].nextNode;
	while (nodep != NULL) {
		if (getArray(arr, isAppeared, numAppeared, adjList, nodep->node) == -1) {
			break;
		}
		nodep = nodep->nextNode;
	}
	if (nodep != NULL) {
		return -1;
	}
	arr[*numAppeared] = node;
	*numAppeared += 1;
	return 0;
}

int findCycle(const Node* adjList, int* isAppeared, const int* path, const int node, const int numVertex) {
	if (path[node] == 1) {
		return -1;
	}
	if (isAppeared[node] == 1) {
		return 0;
	}
	isAppeared[node] = 1;
	int* newPath = (int*)malloc((numVertex + 1) * sizeof(int));
	memcpy(newPath, path, (numVertex + 1) * sizeof(int));
	newPath[node] = 1;
	const Node* nodep = adjList[node].nextNode;
	while (nodep != NULL) {
		if (findCycle(adjList, isAppeared, newPath, nodep->node, numVertex) == -1) {
			free(newPath);
			return -1;
		}
		nodep = nodep->nextNode;
	}
	free(newPath);
	return 0;
}

int main() {
	int numSingers, numClues, leftSinger, rightSinger, numAppeared = 0, sizeArr;
	scanf("%d %d", &numSingers, &numClues);
	int i, k, errorFlag = 0;
	int* arr = (int*)calloc(numSingers, sizeof(int));
	int* isAppeared = (int*)calloc(numSingers + 1, sizeof(int));
	int* path = (int*)calloc(numSingers + 1, sizeof(int));
	int* isLinked = (int*)calloc(numSingers + 1, sizeof(int));
	Node* adjList = (Node*)calloc(numSingers + 1, sizeof(Node));
	Node* nodep;

	for (i = 1; i <= numSingers; i++) {
		adjList[i].node = i;
		adjList[i].lastNode = &adjList[i];
	}
	for (i = 0; i < numClues; i++) {
		scanf("%d", &sizeArr);
		for (k = 0; k < sizeArr; k++) {
			scanf("%d", &arr[k]);
		}
		for (k = 0; k < sizeArr - 1; k++) {
			leftSinger = arr[k];
			rightSinger = arr[k + 1];
			nodep = adjList[leftSinger].lastNode;
			nodep->nextNode = (Node*)calloc(1, sizeof(Node));
			adjList[leftSinger].lastNode = nodep->nextNode;
			nodep->nextNode->node = rightSinger;
			isLinked[rightSinger] = 1;
			if (isLinked[leftSinger] == 0) {
				adjList[leftSinger].isRoot = 1;
				adjList[rightSinger].isRoot = 0;
				isLinked[leftSinger] = 1;
			}
		}
	}

	for (i = 1; i <= numSingers; i++) {
		if (adjList[i].isRoot == 0) {
			continue;
		}
		errorFlag = findCycle(adjList, isAppeared, path, i, numSingers);
		memset(isAppeared, 0, (numSingers + 1) * sizeof(int));
		if (errorFlag == -1) {
			break;
		}
	}
	if (errorFlag == -1) {
		printf("0");
	}
	else {
		for (i = 1; i <= numSingers; i++) {
			if (adjList[i].isRoot == 0) {
				continue;
			}
			getArray(arr, isAppeared, &numAppeared, adjList, i);
		}
		for (i = numAppeared - 1; i >= 0; i--) {
			printf("%d\n", arr[i]);
		}
		for (i = 1; i <= numSingers; i++) {
			if (isAppeared[i] == 0) {
				printf("%d\n", i);
			}
		}
	}

	free(isAppeared);
	free(isLinked);
	free(arr);
	Node* cur, * right;
	for (i = 1; i <= numSingers; i++) {
		right = adjList[i].nextNode;
		while (right != NULL) {
			cur = right;
			right = right->nextNode;
			free(cur);
		}
	}
	free(adjList);
	return 0;
}