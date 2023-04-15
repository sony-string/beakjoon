#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef LLONG_MAX
#define LLONG_MAX 9223372036854775807
#endif

typedef struct Heap {
	int numNodes;
	int* heap;
} Heap;

void createHeap(Heap* heap) {
	heap->numNodes = 0;
	heap->heap = (int*)malloc(5000 * sizeof(int));
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

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
	int result[3];
	int* liquids;
	int l, r, m, firstLiquid, secondLiquid, temp, flag;
	int numLiquids;
	long long best = LLONG_MAX, sum, tempLong;
	Heap heap;
	createHeap(&heap);
	scanf("%d", &numLiquids);
	int i;
	liquids = (int*)malloc(numLiquids * sizeof(int));
	for (i = 0; i < numLiquids; i++) {
		scanf("%d", &temp);
		push(&heap, temp);
	}
	for (i = 0; i < numLiquids; i++) {
		liquids[i] = pop(&heap);
	}
	for (firstLiquid = 0; firstLiquid <= numLiquids - 3; firstLiquid++) {
		for (secondLiquid = firstLiquid + 2; secondLiquid < numLiquids; secondLiquid++) {
			sum = (long long)liquids[firstLiquid] + liquids[secondLiquid];
			l = firstLiquid + 1;
			r = secondLiquid - 1;
			while (r >= l) {
				m = (r + l) / 2;
				tempLong = sum + liquids[m];
				flag = 0;
				if (tempLong < 0) {
					tempLong *= -1;
					flag = 1;
				}
				if (tempLong < best) {
					best = tempLong;
					result[0] = firstLiquid;
					result[1] = secondLiquid;
					result[2] = m;
					//printf("now : %d %d %d\n", liquids[result[0]], liquids[result[2]], liquids[result[1]]);
				}
				if (tempLong == 0) {
					break;
				}
				if (flag == 0) {
					r = m - 1;
					continue;
				}
				l = m + 1;
			}
			if (r >= l) {
				break;
			}
		}
		if (secondLiquid < numLiquids) {
			break;
		}
	}
	
	printf("%d %d %d", liquids[result[0]], liquids[result[2]], liquids[result[1]]);
	free(liquids);
	return 0;
}