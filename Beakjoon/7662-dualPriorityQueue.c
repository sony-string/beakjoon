#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
	int numNodes;
	int* heap;
} Heap;

void createHeap(Heap* heap) {
	heap->numNodes = 0;
	heap->heap = (int*)malloc(1000000 * sizeof(int));
}

void initializeHeap(Heap* heap) {
	heap->numNodes = 0;
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

//standard Max Heap dequeue
int _pop(Heap* heap) {
	if (heap->numNodes == 0) {
		return 0;
	}
	int item = heap->heap[0];
	int left, right, index, bigger;
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
			if (heap->heap[left] > heap->heap[index]) {
				swap(&(heap->heap[left]), &(heap->heap[index]));
			}
			return item;
		}
		if (heap->heap[left] > heap->heap[right]) {
			bigger = left;
		}
		else {
			bigger = right;
		}
		if (heap->heap[bigger] > heap->heap[index]) {
			swap(&(heap->heap[bigger]), &(heap->heap[index]));
			index = bigger;
			continue;
		}
		break;
	}
	return item;
}

//standard Min Heap dequeue
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

int pop(Heap* heap, Heap* garbage) {
	int item = _pop(heap);
	if (garbage->numNodes > 0) {
		while (item == garbage->heap[0]) {
			_pop(garbage);
			item = _pop(heap);
			if (garbage->numNodes == 0) {
				break;
			}
		}
	}
	return item;
}

int popMin(Heap* heap, Heap* garbage) {
	int item = _popMin(heap);
	if (garbage->numNodes > 0) {
		while (item == garbage->heap[0]) {
			_popMin(garbage);
			item = _popMin(heap);
			if (garbage->numNodes == 0) {
				break;
			}
		}
	}
	return item;
}

void push(Heap* heap, int item) {
	heap->heap[heap->numNodes] = item;
	int parent,index;
	index = heap->numNodes;
	heap->numNodes++;
	parent = (index - 1) / 2;
	while (parent != 0) {
		if (heap->heap[parent] < heap->heap[index]) {
			swap(&(heap->heap[parent]), &(heap->heap[index]));
			index = parent;
			parent = (index - 1) / 2;
			continue;
		}
		break;
	}
	if (parent == 0) {
		if (heap->heap[parent] < heap->heap[index]) {
			swap(&(heap->heap[parent]), &(heap->heap[index]));
		}
	}
}

void pushMin(Heap* heap, int item) {
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
	Heap maxHeap, minHeap, garbageMaxHeap, garbageMinHeap;
	createHeap(&maxHeap);
	createHeap(&minHeap);
	createHeap(&garbageMaxHeap);
	createHeap(&garbageMinHeap);
	char operation;
	int item, numCases, numLines, numItems;
	int i;
	scanf("%d", &numCases);
	int T, L;
	for (T = 0; T < numCases; T++) {
		scanf("%d", &numLines);
		initializeHeap(&maxHeap);
		initializeHeap(&minHeap);
		initializeHeap(&garbageMaxHeap);
		initializeHeap(&garbageMinHeap);
		numItems = 0;
		for (L = 0; L < numLines; L++) {
			scanf("%c", &operation);			
			while (operation == '\n') {
				scanf("%c", &operation);
			}
			if (operation == 'I') {
				scanf("%d", &item);
				push(&maxHeap, item);
				pushMin(&minHeap, item);
				numItems++;
				continue;
			}
			if (operation == 'D') {
				scanf("%d", &i);
				if (numItems == 0) {
					continue;
				}
				numItems--;
				if (i == 1) {
					item = pop(&maxHeap, &garbageMaxHeap);
					//printf("Max Heap : %d\n", item);
					pushMin(&garbageMinHeap, item);
				}
				if(i == -1) {
					item = popMin(&minHeap, &garbageMinHeap);
					//printf("Min Heap : %d\n", item);
					push(&garbageMaxHeap, item);
				}
			}
		}
		if (numItems == 0) {
			printf("EMPTY\n");
			continue;
		}
		item = pop(&maxHeap, &garbageMaxHeap);
		pushMin(&garbageMinHeap, item);
		numItems--;
		printf("%d ", item);
		if (numItems == 0) {
			printf("%d\n", item);
			continue;
		}
		item = popMin(&minHeap, &garbageMinHeap);
		printf("%d\n", item);
	}

	free(maxHeap.heap);
	free(minHeap.heap);
	free(garbageMaxHeap.heap);
	free(garbageMinHeap.heap);
	return 0;
}