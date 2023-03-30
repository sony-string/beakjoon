#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
	int numNodes;
	int* heap;
} Heap;

void createHeap(Heap* heap, int size) {
	heap->numNodes = 0;
	heap->heap = (int*)malloc(size * sizeof(int));
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int _popMin(Heap* heap) {
	if (heap->numNodes == 0) {
		return 0;
	}
	int item = heap->heap[0];
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
			if (heap->heap[left] < heap->heap[index]) {
				swap(&(heap->heap[left]), &(heap->heap[index]));
			}
			return item;
		}
		if (heap->heap[left] < heap->heap[right]) {
			smaller = left;
		}
		else {
			smaller = right;
		}
		if (heap->heap[smaller] < heap->heap[index]) {
			swap(&(heap->heap[smaller]), &(heap->heap[index]));
			index = smaller;
			continue;
		}
		break;
	}
	return item;
}

void push(Heap* heap, int item) {
	heap->heap[heap->numNodes] = item;
	int parent, index;
	index = heap->numNodes;
	heap->numNodes++;
	parent = (index - 1) / 2;
	while (parent != 0) {
		if (heap->heap[parent] > heap->heap[index]) {
			swap(&(heap->heap[parent]), &(heap->heap[index]));
			index = parent;
			parent = (index - 1) / 2;
			continue;
		}
		break;
	}
	if (parent == 0) {
		if (heap->heap[parent] > heap->heap[index]) {
			swap(&(heap->heap[parent]), &(heap->heap[index]));
		}
	}
}

int main() {
	int l, r, m, pos, numPoints, numPointsSet = 0;
	int* sorted;
	int* pointArr;
	Heap minHeap;
	scanf("%d", &numPoints);
	createHeap(&minHeap, numPoints);
	sorted = (int*)malloc(numPoints * sizeof(int));
	pointArr = (int*)malloc(numPoints * sizeof(int));
	int i;
	for (i = 0; i < numPoints; i++) {
		scanf("%d", &pos);
		push(&minHeap, pos);
		pointArr[i] = pos;
	}
	sorted[numPointsSet] = _popMin(&minHeap);
	numPointsSet++;
	for (i = 0; i < numPoints; i++) {
		pos = _popMin(&minHeap);
		if (pos == sorted[numPointsSet - 1]) {
			continue;
		}
		sorted[numPointsSet] = pos;
		numPointsSet++;
	}
	
	for (i = 0; i < numPoints; i++) {
		l = 0; r = numPointsSet - 1;
		while (1) {
			m = (l + r) / 2;
			if (sorted[m] > pointArr[i]) {
				r = m - 1;
				continue;
			}
			if (sorted[m] == pointArr[i]) {
				printf("%d ", m);
				break;
			}
			l = m + 1;
		}
	}
	free(sorted);
	free(pointArr);
	free(minHeap.heap);

	return 0;
}