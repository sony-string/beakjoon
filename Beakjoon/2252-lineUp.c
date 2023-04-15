#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int node;
	int isRoot;
	struct Node* nextNode;
	struct Node* lastNode;
} Node;

int getArray(int* arr, int* isAppeared, int* numAppeared, const Node* adjList, int node) {
	if (isAppeared[node] == 1) {
		return -1;
	}
	isAppeared[node] = 1;
	const Node* nodep = adjList[node].nextNode;
	while (nodep != NULL) {
		getArray(arr, isAppeared, numAppeared, adjList, nodep->node);
		nodep = nodep->nextNode;
	}
	arr[*numAppeared] = node;
	isAppeared[node] = 1;
	*numAppeared += 1;
	return 0;
}

int main() {
	int numStudents, numClues, leftStudent, rightStudent, numAppeared = 0;
	scanf("%d %d", &numStudents, &numClues);
	int i;
	int* arr = (int*)calloc(numStudents, sizeof(int));
	int* isAppeared = (int*)calloc(numStudents + 1, sizeof(int));
	int* isLinked = (int*)calloc(numStudents + 1, sizeof(int));
	Node* adjList = (Node*)calloc(numStudents + 1, sizeof(Node));
	Node* nodep;

	for (i = 1; i <= numStudents; i++) {
		adjList[i].node = i;
		adjList[i].lastNode = &adjList[i];
	}
	for (i = 0; i < numClues; i++) {
		scanf("%d %d", &leftStudent, &rightStudent);
		nodep = adjList[leftStudent].lastNode;
		nodep->nextNode = (Node*)calloc(1, sizeof(Node));
		adjList[leftStudent].lastNode = nodep->nextNode;
		nodep->nextNode->node = rightStudent;
		isLinked[rightStudent] = 1;
		if (isLinked[leftStudent] == 0) {
			adjList[leftStudent].isRoot = 1;
			isLinked[leftStudent] = 1;
		}
	}

	for (i = 1; i <= numStudents; i++) {
		if (adjList[i].isRoot == 0) {
			continue;
		}
		//printf("%d is root! \n", i);
		getArray(arr, isAppeared, &numAppeared, adjList, i);
		//printf("\n");
	}
	for (i = numAppeared -1; i >= 0; i--) {
		printf("%d ", arr[i]);
	}
	for (i = 1; i < numStudents; i++) {
		if (isAppeared[i] == 0) {
			printf("%d ", i);
		}
	}

	free(isAppeared);
	free(isLinked);
	free(arr);
	Node* cur, * right;
	for (i = 1; i <= numStudents; i++) {
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