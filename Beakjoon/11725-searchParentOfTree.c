#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	struct Node* nextNode;
	int item;
}Node;

void recordParent(int* parentInfo, const Node* adjList, int node) {
	int parent = parentInfo[node];
	Node *nodep = adjList[node].nextNode;
	while (nodep != NULL) {
		if (nodep->item != parentInfo[node]) {
			parentInfo[nodep->item] = node;
			recordParent(parentInfo, adjList, nodep->item);
		}
		nodep = nodep->nextNode;
	}
}

int main() {
	int numNodes, src, dst;
	int* parentInfo;
	Node* adjList;
	Node* srcNode, *dstNode, *nodep;
	scanf("%d", &numNodes);
	parentInfo = (int*)calloc((numNodes + 1), sizeof(int));
	adjList = (Node*)calloc((numNodes + 1), sizeof(Node));
	int i;
	for (i = 0; i <= numNodes; i++) {
		adjList[i].item = i;
	}
	for (i = 0; i < numNodes - 1; i++) {
		scanf("%d %d", &src, &dst);
		dstNode = (Node*)calloc(1, sizeof(Node));
		dstNode->item = dst;
		srcNode = (Node*)calloc(1, sizeof(Node));
		srcNode->item = src;

		nodep = &adjList[src];
		while (nodep->nextNode != NULL) {
			nodep = nodep->nextNode;
		}
		nodep->nextNode = dstNode;

		nodep = &adjList[dst];
		while (nodep->nextNode != NULL) {
			nodep = nodep->nextNode;
		}
		nodep->nextNode = srcNode;
	}
	recordParent(parentInfo, adjList, 1);

	for (i = 2; i <= numNodes; i++) {
		printf("%d\n", parentInfo[i]);
	}

	free(parentInfo);
	Node** stackNodes = (Node**)malloc(numNodes * sizeof(Node*));
	int r, k;
	for (i = 1; i <= numNodes; i++) {
		r = 0;
		nodep = &adjList[i];
		while (nodep->nextNode != NULL) {
			stackNodes[r] = nodep->nextNode;
			r++;
			nodep = nodep->nextNode;
		}
		for (k = r - 1; k >= 0; k--) {
			free(stackNodes[k]);
		}
	}
	free(adjList);
	return 0;
}