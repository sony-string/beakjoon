#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
	int numNodes;
	int* heap;
} Heap;

void createHeap(Heap* heap) {
	heap->numNodes = 0;
	heap->heap = (int*)malloc(100000 * sizeof(int));
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

//return its item of min value
int pop(Heap* heap) {
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
	Heap minHeap;
	createHeap(&minHeap);
	int numLines, num;
	scanf("%d", &numLines);

	int i;
	for (i = 0; i < numLines; i++) {
		scanf("%d", &num);
		if (num > 0) {
			push(&minHeap, num);
			continue;
		}
		printf("%d\n", pop(&minHeap));
	}

	free(minHeap.heap);
	return 0;
}