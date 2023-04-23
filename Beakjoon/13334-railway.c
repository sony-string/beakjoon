#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

#define END_POS 100000000

enum {
	home = 0, job = 1
};

typedef struct Pair {
	int number;
	int pos[2];
} Pair;

typedef struct Heap {
	Pair** heap;
	int numNodes;
} Heap;

void swapInt(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void swap(Pair** a, Pair** b) {
	Pair* temp = *a;
	*a = *b;
	*b = temp;
}

Pair* pop(Heap* heap, int* heapMap, int type) {
	if (heap->numNodes == 0) {
		return 0;
	}
	Pair* item = heap->heap[0];
	int left, right, index, smaller;
	index = 0;
	heap->numNodes--;
	heap->heap[0] = heap->heap[heap->numNodes];
	heapMap[heap->heap[0]->number] = 0;
	heapMap[item->number] = -1;

	while (index < heap->numNodes) {
		left = index * 2 + 1;
		right = index * 2 + 2;
		if (left >= heap->numNodes) {
			return item;
		}
		if (left == heap->numNodes - 1) {
			if (heap->heap[left]->pos[type] < heap->heap[index]->pos[type]) {
				swap(&(heap->heap[left]), &(heap->heap[index]));
				swapInt(&heapMap[heap->heap[left]->number], &heapMap[heap->heap[index]->number]);
			}
			return item;
		}
		if (heap->heap[left]->pos[type] < heap->heap[right]->pos[type]) {
			smaller = left;
		}
		else {
			smaller = right;
		}
		if (heap->heap[smaller]->pos[type] < heap->heap[index]->pos[type]) {
			swap(&(heap->heap[smaller]), &(heap->heap[index]));
			swapInt(&heapMap[heap->heap[smaller]->number], &heapMap[heap->heap[index]->number]);
			index = smaller;
			continue;
		}
		break;
	}
	return item;
}

void push(Heap* heap, int* heapMap, Pair* pair, int type) {
	heap->heap[heap->numNodes] = pair;
	heapMap[pair->number] = heap->numNodes;
	int parent, index;
	index = heap->numNodes;
	heap->numNodes++;
	parent = (index - 1) / 2;
	while (parent != 0) {
		if (heap->heap[parent]->pos[type] > heap->heap[index]->pos[type]) {
			swap(&(heap->heap[parent]), &(heap->heap[index]));
			swapInt(&heapMap[heap->heap[parent]->number], &heapMap[heap->heap[index]->number]);
			index = parent;
			parent = (index - 1) / 2;
			continue;
		}
		break;
	}
	if (parent == 0) {
		if (heap->heap[parent]->pos[type] > heap->heap[index]->pos[type]) {
			swap(&(heap->heap[parent]), &(heap->heap[index]));
			swapInt(&heapMap[heap->heap[parent]->number], &heapMap[heap->heap[index]->number]);
		}
	}
}

void deleteKey(Heap* heap, int* heapMap, int node, int type) {
	int index = heapMap[node];
	heap->heap[index]->pos[type] = INT_MAX;
	int left, right, smaller;

	while (index < heap->numNodes) {
		left = index * 2 + 1;
		right = index * 2 + 2;
		if (left >= heap->numNodes) {
			break;
		}
		if (left == heap->numNodes - 1) {
			if (heap->heap[left]->pos[type] < heap->heap[index]->pos[type]) {
				swap(&(heap->heap[left]), &(heap->heap[index]));
				swapInt(&heapMap[heap->heap[left]->number], &heapMap[heap->heap[index]->number]);
			}
			break;
		}
		if (heap->heap[left]->pos[type] < heap->heap[right]->pos[type]) {
			smaller = left;
		}
		else {
			smaller = right;
		}
		if (heap->heap[smaller]->pos[type] < heap->heap[index]->pos[type]) {
			swap(&(heap->heap[smaller]), &(heap->heap[index]));
			swapInt(&heapMap[heap->heap[smaller]->number], &heapMap[heap->heap[index]->number]);
			index = smaller;
			continue;
		}
		break;
	}
}

int main() {
	int lenRail, numPersons, count = 0, result = 0, start, end, last = 0;
	Pair** pairArr;
	int* heapMap;
	Heap heap;
	scanf("%d", &numPersons);
	int i;
	pairArr = (Pair**)calloc(numPersons, sizeof(Pair*));
	heapMap = (int*)calloc(numPersons, sizeof(int));
	memset(heapMap, -1, numPersons * sizeof(int));
	heap.heap = (Pair**)calloc(numPersons, sizeof(Pair*));
	heap.numNodes = 0;

	for (i = 0; i < numPersons; i++) {
		pairArr[i] = (Pair*)calloc(1, sizeof(Pair));
		pairArr[i]->number = i;
		scanf("%d %d", &pairArr[i]->pos[home], &pairArr[i]->pos[job]);
		if (pairArr[i]->pos[job] < pairArr[i]->pos[home]) {
			swapInt(&pairArr[i]->pos[job], &pairArr[i]->pos[home]);
		}
		push(&heap, heapMap, pairArr[i], home);
	}
	for (i = 0; i < numPersons; i++) {
		pairArr[i] = pop(&heap, heapMap, home);
	}
	scanf("%d", &lenRail);

	start = pairArr[0]->pos[home];
	if (END_POS - start <= lenRail) {
		end = END_POS;
	}
	else {
		end = start + lenRail;
	}
	//printf("*******start from %d to  %d\n", start, end);
	for (i = 0; i < numPersons; i++) {
		if (pairArr[i]->pos[home] > end) {
			break;
		}
		if (pairArr[i]->pos[job] <= end) {
			count++;
			//printf("include %d, count =  %d\n", pairArr[i]->number + 1, count);
		}
		else {
			push(&heap, heapMap, pairArr[i], job);
		}
	}
	result = count;
	last = i;

	for (i = 1; i < numPersons - result; i++) {
		if (heapMap[pairArr[i - 1]->number] != -1) {
			deleteKey(&heap, heapMap, pairArr[i - 1]->number, job);
		}
		else {
			count--;
			if (pairArr[i - 1]->pos[home] == pairArr[i]->pos[home]) {
				continue;
			}
		}
		start = pairArr[i]->pos[home];
		if (END_POS - start <= lenRail) {
			end = END_POS;
		}
		else {
			end = start + lenRail;
		}
		//printf("*******start from %d to  %d\n", start, end);
		for (; last < numPersons; last++) {
			if (pairArr[last]->pos[home] > end) {
				break;
			}
			if (pairArr[last]->pos[job] <= end) {
				count++;
				//printf("include %d, count = %d\n", pairArr[i]->number + 1, count);
				if (count > result) {
					result++;
				}
			}
			else {
				push(&heap, heapMap, pairArr[last], job);
			}
		}
		while (1) {
			if (heap.numNodes == 0) {
				break;
			}
			if (heap.heap[0]->pos[job] <= end) {
				pop(&heap, heapMap, job);
				//printf("include %d, count = %d\n", pop(&heap, heapMap, job)->number + 1, count + 1);
				count++;
				if (count > result) {
					result++;
				}
			}
			else {
				break;
			}
		}
	}
	printf("%d", result);

	free(heap.heap);
	free(heapMap);
	for (i = 0; i < numPersons; i++) {
		free(pairArr[i]);
	}
	free(pairArr);
	return 0;
}