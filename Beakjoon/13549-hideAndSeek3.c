#include <stdio.h>
#include <stdlib.h>

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

#define SIZE 100001

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
	int* heap, * heapMap;
	int* distArr;
	int starting, goal, last = 0, pos, routeCount;
	int next[3];
	int cost[3];

	scanf("%d %d", &starting, &goal);

	heap = (int*)calloc(SIZE, sizeof(int));
	distArr = (int*)malloc(SIZE * sizeof(int));
	heapMap = (int*)malloc(SIZE * sizeof(int));

	int i;
	for (i = 0; i < SIZE; i++) {
		heap[i] = -1;
		distArr[i] = INT_MAX;
		heapMap[i] = -1;
	}
	distArr[starting] = 0;

	push(heap, &last, heapMap, starting, distArr);

	while (last != 0) {
		pos = pop(heap, &last, heapMap, distArr);
		if (pos == goal) {
			break;
		}
		routeCount = 0;
		if (pos > 0) {
			next[routeCount] = pos - 1;
			cost[routeCount] = 1;
			routeCount++;
		}
		if (pos < 100000) {
			next[routeCount] = pos + 1;
			cost[routeCount] = 1;
			routeCount++;
		}
		if (pos * 2 <= 100000 && pos != 0) {
			next[routeCount] = pos * 2;
			cost[routeCount] = 0;
			routeCount++;
		}
		for (i = 0; i < routeCount; i++) {
			if (distArr[next[i]] == INT_MAX) {
				if (distArr[pos] == INT_MAX) {
					distArr[next[i]] = cost[i];
				}
				else {
					distArr[next[i]] = cost[i] + distArr[pos];
				}
				push(heap, &last, heapMap, next[i], distArr);
				//printf("%d : distArr[%d] <= %d\n", pos, next[i], distArr[next[i]]);
			}
			else {
				if (distArr[pos] + cost[i] < distArr[next[i]]) {
					distArr[next[i]] = cost[i] + distArr[pos];
					decreaseKey(heap, &last, heapMap, next[i], distArr);
					//printf("%d : distArr[%d] <= %d\n", pos, next[i], distArr[next[i]]);
				}
			}
		}
	}
	printf("%d", distArr[goal]);

	free(heap);
	free(heapMap);
	free(distArr);
	return 0;
}