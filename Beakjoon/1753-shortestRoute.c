#include <stdio.h>
#include <stdlib.h>

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

typedef struct Node {
	int dist;
	int node;
	struct Node* nextNode;
	struct Node* lastNode;
} Node;

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void push(int* heap, int* last, int* heapMap, int node, const int* distArr) {
	heap[*last] = node;
	heapMap[node] = *last;
	int parent;
	int index = *last;
	(*last)++;
	
	while (index > 0) {
		parent = (index - 1) / 2;
		if (distArr[heap[parent]] > distArr[node]) {
			swap(&heap[parent], &heap[index]);
			swap(&heapMap[heap[parent]], &heapMap[heap[index]]);
			index = parent;
			continue;
		}
		break;
	}
}

int pop(int* heap, int* last, int* heapMap, const int* distArr) {
	int left = 1, right = 2, index = 0, minIndex;
	int returnValue = heap[0];
	heapMap[returnValue] = -1;
	(*last)--;
	heap[0] = heap[*last];
	heapMap[heap[0]] = 0;
	heap[*last] = -1;
	while (right < *last) {
		if (distArr[heap[right]] > distArr[heap[left]]) {
			minIndex = left;
		}
		else {
			minIndex = right;
		}
		if (distArr[heap[index]] > distArr[heap[minIndex]]) {
			swap(&heap[minIndex], &heap[index]);
			swap(&heapMap[heap[minIndex]], &heapMap[heap[index]]);
			index = minIndex;
		}
		else {
			break;
		}
		left = index * 2 + 1;
		right = index * 2 + 2;
	}
	if (left == *last - 1) {
		minIndex = left;
		if (distArr[heap[index]] > distArr[heap[minIndex]]) {
			swap(&heap[minIndex], &heap[index]);
			swap(&heapMap[heap[minIndex]], &heapMap[heap[index]]);
		}
	}
	return returnValue;
}

void decreaseKey(int* heap, int* last, int* heapMap, int node, const int* distArr) {
	int index = heapMap[node];
	int parent;

	while (index > 0) {
		parent = (index - 1) / 2;
		if (distArr[heap[parent]] > distArr[node]) {
			swap(&heap[parent], &heap[index]);
			swap(&heapMap[heap[parent]], &heapMap[heap[index]]);
			index = parent;
			continue;
		}
		break;
	}
}

int main() {

	//FILE* fp = freopen("input.txt", "r", stdin);

	int* distArr;
	int* heapMap, *heap;
	int numVertices, numEdges, starting;
	int last = 0, i, src, dst, dist, node;
	Node* adjList;
	Node* nodep, *iteratorNode;
	scanf("%d %d", &numVertices, &numEdges);
	scanf("%d", &starting);
	starting--;

	adjList = (Node*)calloc(numVertices, sizeof(Node));
	heap = (int*)calloc(numVertices, sizeof(int));
	distArr = (int*)malloc(numVertices * sizeof(int));
	heapMap = (int*)malloc(numVertices * sizeof(int));
	for (i = 0; i < numVertices; i++) {
		distArr[i] = INT_MAX;
		adjList[i].node = i;
		heapMap[i] = -1;
		heap[i] = -1;
		adjList[i].lastNode = &adjList[i];
	}
	distArr[starting] = 0;


	for (i = 0; i < numEdges; i++) {
		scanf("%d %d %d", &src, &dst, &dist);
		src--; dst--;
		nodep = (Node*)calloc(1, sizeof(Node));
		nodep->node = dst;
		nodep->dist = dist;
		iteratorNode = &adjList[src];
		adjList[src].lastNode->nextNode = nodep;
		adjList[src].lastNode = nodep;
	}

	heap[last] = starting;
	heapMap[starting] = last;
	last++;
	while (last != 0) {
		/*
		printf("Heap >> ");
		for (i = 0; i < last; i++) {
			printf("%d ", heap[i] + 1);
		}
		
		printf("\n");
		*/
		node = pop(heap, &last, heapMap, distArr);
		//printf("\n\nsearching %d", node+1); 
		iteratorNode = adjList[node].nextNode;
		while (iteratorNode != NULL) {
			//printf("   add %d... ", iteratorNode->node + 1);
			if (distArr[iteratorNode->node] == INT_MAX) {
				if (distArr[node] != INT_MAX) {
					distArr[iteratorNode->node] = distArr[node] + iteratorNode->dist;
				}
				else {
					distArr[iteratorNode->node] = iteratorNode->dist;
				}
				push(heap, &last, heapMap, iteratorNode->node, distArr);
				//printf("%d : distArr[%d] <= %d\n", node + 1, iteratorNode->node + 1, distArr[iteratorNode->node]);
			}
			else {
				if (distArr[node] != INT_MAX) {
					if (distArr[iteratorNode->node] > distArr[node] + iteratorNode->dist) {
						distArr[iteratorNode->node] = distArr[node] + iteratorNode->dist;
						decreaseKey(heap, &last, heapMap, iteratorNode->node, distArr);
						//printf("%d : distArr[%d] <= %d\n", node + 1, iteratorNode->node + 1, distArr[iteratorNode->node]);
					}
				}
			}
			iteratorNode = iteratorNode->nextNode;
		}
	}

	//fclose(fp);

	for (i = 0; i < numVertices; i++) {
		if (distArr[i] != INT_MAX) {
			printf("%d\n", distArr[i]);
		}
		else {
			printf("INF\n");
		}
	}

	Node** stackNodes = (Node**)malloc(numEdges * sizeof(Node*));
	int r, k;
	for (i = 0; i < numVertices; i++) {
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
	free(heap);
	return 0;
}