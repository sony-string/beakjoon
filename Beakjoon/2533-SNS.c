#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int value;
	struct Node* nextNode;
	struct Node* lastNode;
} Node;

int searchTree(int* degrees, Node** adjList, Node* node, Node* parent) {
	int count = 0;
	Node* next = node->nextNode;
	while (next != NULL) {
		if (next->value == parent->value) {
			next = next->nextNode;
			continue;
		}
		count += searchTree(degrees, adjList, adjList[next->value], node);
		next = next->nextNode;
	}
	if (parent == node) {
		if (degrees[node->value] >= 1) {
			//printf("coloring = %d\n", node->value);
			return count + 1;
		}
		return count;
	}
	if (degrees[node->value] == 1) {
		return count;
	}

	degrees[parent->value] --;
	//printf("coloring = %d\n", node->value);
	return count + 1;
}

int solve(Node** adjList, int* degrees) {
	int size = adjList[0]->value;
	int* newDegrees = (int*)calloc(size + 1, sizeof(int));
	memcpy(newDegrees, degrees, (size + 1) * sizeof(int));
	return 0;
}

int main() {
	Node** adjList, * node;
	int numNodes, src, dst, result = 0, last = 0;
	int* degrees;
	scanf("%d", &numNodes);
	adjList = (Node**)calloc(numNodes + 1, sizeof(Node*));
	degrees = (int*)calloc(numNodes + 1, sizeof(int));

	int i;
	for (i = 0; i <= numNodes; i++) {
		adjList[i] = (Node*)calloc(1, sizeof(Node));
		adjList[i]->value = i;
		adjList[i]->lastNode = adjList[i];
	}
	adjList[0]->value = numNodes;
	for (i = 0; i < numNodes - 1; i++) {
		scanf("%d %d", &src, &dst);
		node = (Node*)calloc(1, sizeof(Node));
		node->value = dst;
		adjList[src]->lastNode->nextNode = node;
		adjList[src]->lastNode = node;
		degrees[src]++;

		node = (Node*)calloc(1, sizeof(Node));
		node->value = src;
		adjList[dst]->lastNode->nextNode = node;
		adjList[dst]->lastNode = node;
		degrees[dst]++;
	}

	result = searchTree(degrees, adjList, adjList[1], adjList[1]);

	printf("%d", result);

	return 0;
}