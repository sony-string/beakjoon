#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	struct Node* nextNode;
	int item;
	int distance;
}Node;

int getDistancesDfs(int *distArr, const Node* adjList, int node, int beforeNode) {
	int longest = 0, secondLongest = 0, temp = 0;
	Node* nodep = adjList[node].nextNode;
	while (nodep != NULL) {
		if (nodep->item != beforeNode) {
				temp = nodep->distance + getDistancesDfs(distArr, adjList, nodep->item, node);

			if (secondLongest < temp) {
				secondLongest = temp;
				if (longest < secondLongest) {
					temp = longest;
					longest = secondLongest;
					secondLongest = temp;
				}
			}
		}
		nodep = nodep->nextNode;
	}
	distArr[node] = longest + secondLongest;
	return longest;
}

int main() {
	Node* adjList;
	int numNodes, diameter = 0;
	int i, next = 0, distance = 0, node;
	int* distances;
	Node* nodep, * lastNode;

	scanf("%d", &numNodes);
	adjList = (Node*)calloc(numNodes + 1, sizeof(Node));
	distances = (int*)calloc(numNodes + 1, sizeof(int));

	for (i = 1; i <= numNodes; i++) {
		scanf("%d", &node);
		adjList[node].item = node;
		lastNode = &adjList[node];
		while (1) {
			scanf("%d", &next);
			if (next == -1) {
				break;
			}
			scanf("%d", &distance);
			nodep = (Node*)calloc(1, sizeof(Node));
			nodep->item = next;
			nodep->distance = distance;
			lastNode->nextNode = nodep;
			lastNode = nodep;
		}
	}

	getDistancesDfs(distances, adjList, 1, 0);
	diameter = distances[1];
	for (i = 2; i <= numNodes; i++) {
		if (distances[i] > diameter) {
			diameter = distances[i];
		}
	}
	printf("%d", diameter);

	Node** stackNodes = (Node**)malloc(numNodes * sizeof(Node*));
	int r, k;
	for (i = 1; i <= numNodes; i++) {
		r = 0;
		nodep = &adjList[i];
		while (nodep->nextNode == NULL) {
			stackNodes[r] = nodep->nextNode;
			r++;
		}
		for (k = r - 1; k >= 0; k--) {
			free(stackNodes[k]);
		}
	}
	free(stackNodes);
	free(adjList);
	free(distances);

	return 0;
}