#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
	int numNodes;
	int** heap;
} Heap;

void createHeap(Heap* heap) {
	heap->numNodes = 0;
	heap->heap = (int**)malloc(100000 * sizeof(int*));
}

void deleteHeap(Heap* heap) {
	int i;
	for (i = 0; i < heap->numNodes; i++) {
		free(heap->heap[i]);
	}
	free(heap->heap);
	heap->numNodes = 0;
}


void swap(int** a, int** b) {
	int* temp = *a;
	*a = *b;
	*b = temp;
}

int* pop(Heap* heap) {
	if (heap->numNodes == 0) {
		return 0;
	}
	int* item = heap->heap[0];
	int left, right, index, smaller;
	index = 0;
	heap->numNodes--;
	heap->heap[0] = heap->heap[heap->numNodes];
	while (index < heap->numNodes) {
		left = index * 2 + 1;
		right = index * 2 + 2;
		if (left >= heap->numNodes) {
			return item;
		}
		if (left == heap->numNodes - 1) {
			if (heap->heap[left][2] < heap->heap[index][2]) {
				swap(&(heap->heap[left]), &(heap->heap[index]));
			}
			return item;
		}
		if (heap->heap[left][2] < heap->heap[right][2]) {
			smaller = left;
		}
		else {
			smaller = right;
		}
		if (heap->heap[smaller][2] < heap->heap[index][2]) {
			swap(&(heap->heap[smaller]), &(heap->heap[index]));
			index = smaller;
			continue;
		}
		break;
	}
	return item;
}

void pushMin(Heap* heap, int* edge) {
	int* item = (int*)malloc(3 * sizeof(int));
	item[0] = edge[0];
	item[1] = edge[1];
	item[2] = edge[2];
	heap->heap[heap->numNodes] = item;
	int parent, index;
	index = heap->numNodes;
	heap->numNodes++;
	parent = (index - 1) / 2;
	while (parent != 0) {
		if (heap->heap[parent][2] > heap->heap[index][2]) {
			swap(&(heap->heap[parent]), &(heap->heap[index]));
			index = parent;
			parent = (index - 1) / 2;
			continue;
		}
		break;
	}
	if (parent == 0) {
		if (heap->heap[parent][2] > heap->heap[index][2]) {
			swap(&(heap->heap[parent]), &(heap->heap[index]));
		}
	}
}

int main() {
	int* rootIndex, * unioned;
	int numVertices, numEdges, weight = 0, root, indexSrc = 0, indexDst = 0;
	int* edge = (int*)malloc(3 * sizeof(int));

	Heap heap;
	createHeap(&heap);
	scanf("%d %d", &numVertices, &numEdges);
	rootIndex = (int*)calloc(numVertices + 1, sizeof(int));
	unioned = (int*)calloc(numVertices + 1, sizeof(int));
	int i;
	for (i = 0; i < numEdges; i++) {
		scanf("%d %d %d", edge, edge + 1, edge + 2);
		pushMin(&heap, edge);
	}
	free(edge);
	edge = pop(&heap);
	weight += edge[2];
	rootIndex[edge[0]] = edge[0];
	rootIndex[edge[1]] = edge[0];
	root = edge[0];
	unioned[edge[0]] = root;

	while (heap.numNodes != 0) {
		edge = pop(&heap);
		indexSrc = unioned[rootIndex[edge[0]]];
		indexDst = unioned[rootIndex[edge[1]]];
		if (indexSrc != 0) {
			while (unioned[indexSrc] != indexSrc && indexSrc != root) {
				indexSrc = unioned[indexSrc];
			}
		}
		if (indexDst != 0) {
			while (unioned[indexDst] != indexDst && indexDst != root) {
				indexDst = unioned[indexDst];
			}
		}
		if (indexSrc == indexDst && indexSrc != 0) {
			free(edge);
			continue;
		}

		weight += edge[2];
		if (rootIndex[edge[0]] == 0 && rootIndex[edge[1]] == 0) {
			rootIndex[edge[0]] = edge[0];
			rootIndex[edge[1]] = edge[0];
			unioned[edge[0]] = edge[0];
			free(edge);
			continue;
		}
		if (rootIndex[edge[0]] == 0) {
			rootIndex[edge[0]] = rootIndex[edge[1]];
			free(edge);
			continue;
		} 
		else if (rootIndex[edge[1]] == 0) {
			rootIndex[edge[1]] = rootIndex[edge[0]];
			free(edge);
			continue;
		}

		if (indexSrc == root) {
			unioned[indexDst] = root;
		}
		else if (indexDst == root) {
			unioned[indexSrc] = root;
		}
		else {
			unioned[indexDst] = indexSrc;
		}
		free(edge);
	}

	printf("%d", weight);
	deleteHeap(&heap);
	free(rootIndex);
	return 0;
}