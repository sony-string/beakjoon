#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int index;
	int degree;
	struct Node* nextNode;
	struct Node* lastNode;
} Node;

typedef struct Heap {
	int* heap;
	int numNodes;
} Heap;

void swap(int* arr, int src, int dst) {
	int temp = arr[src];
	arr[src] = arr[dst];
	arr[dst] = temp;
}

void push(Heap* heap, int node) {
	int cur, parent;

	heap->numNodes++;
	cur = heap->numNodes;
	heap->heap[cur] = node;

	while (cur > 1) {
		parent = cur / 2;
		if (heap->heap[parent] > node) {
			swap(heap->heap, cur, parent);
			cur = parent;
			continue;
		}
		break;
	}
}

int pop(Heap* heap) {
	if (heap->numNodes == 0) {
		return -1;
	}
	int cur, left, right, min, node;
	int returnValue = heap->heap[1];
	heap->heap[1] = heap->heap[heap->numNodes];
	node = heap->heap[1];
	heap->numNodes -= 1;
	cur = 1;
	left = 2; right = 3;
	while (right <= heap->numNodes) {
		min = heap->heap[left] < heap->heap[right] ? left : right;
		if (heap->heap[min] < node) {
			swap(heap->heap, min, cur);
			cur = min;
			left = cur * 2;
			right = left + 1;
			continue;
		}
		break;
	}

	if (left == heap->numNodes) {
		min = left;
		if (heap->heap[min] < node) {
			swap(heap->heap, min, cur);
		}
	}
	return returnValue;
}


int main() {
	Node* adjList, * node;
	Heap heap;
	int numQ, numInfo;
	int befo, next;


	scanf("%d %d", &numQ, &numInfo);
	adjList = (Node*)calloc(numQ + 1, sizeof(Node));
	heap.heap = (int*)malloc((numQ + 2) * sizeof(int));
	heap.numNodes = 0;

	for (int i = 1; i <= numQ; i++) {
		adjList[i].index = i;
		adjList[i].lastNode = &adjList[i];
	}
	
	for (int i = 0; i < numInfo; i++) {
		scanf("%d %d", &befo, &next);
		node = (Node*)calloc(1, sizeof(Node));
		node->index = next;
		adjList[befo].lastNode->nextNode = node;
		adjList[befo].lastNode = node;
		adjList[next].degree += 1;
	}

	for (int i = 1; i <= numQ; i++) {
		if (adjList[i].degree == 0) {
			push(&heap, i);
		}
	}

	while (heap.numNodes != 0) {
		node = &adjList[pop(&heap)];
		printf("%d ", node->index);
		node = node->nextNode;
		while (node != NULL) {
			next = node->index;
			adjList[next].degree -= 1;
			if (adjList[next].degree == 0) {
				push(&heap, next);
			}
			node = node->nextNode;
		}
	}
	return 0;
}