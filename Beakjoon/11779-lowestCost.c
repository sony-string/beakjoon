#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int index;
	int value;
	struct Node* nextNode;
	struct Node* lastNode;
} Node;

typedef struct Heap {
	int numNodes;
	int* heap;
	int* heapMap;
} Heap;

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void push(Heap* heap, int node, int* priority) {
	int cur, parent;
	heap->numNodes += 1;
	cur = heap->numNodes;
	heap->heap[cur] = node;
	heap->heapMap[node] = cur;
	while (cur > 1) {
		parent = cur / 2;
		if (priority[heap->heap[parent]] > priority[node]) {
			swap(&heap->heapMap[heap->heap[parent]], &heap->heapMap[node]);
			swap(&heap->heap[parent], &heap->heap[cur]);
			cur = parent;
			continue;
		}
		else {
			break;
		}
	}
}

int pop(Heap* heap, int* priority) {
	int cur, left, right, min;
	int returnValue = heap->heap[1];
	heap->heapMap[returnValue] = -1;
	cur = heap->numNodes;
	heap->numNodes -= 1;
	if (cur == 1) {
		return returnValue;
	}
	heap->heapMap[heap->heap[cur]] = 1;
	heap->heap[1] = heap->heap[cur];

	cur = 1;
	left = 2;
	right = 3;
	while (right <= heap->numNodes) {
		min = priority[heap->heap[left]] < priority[heap->heap[right]] ? left : right;
		if (priority[heap->heap[cur]] > priority[heap->heap[min]]) {
			swap(&heap->heapMap[heap->heap[cur]], &heap->heapMap[heap->heap[min]]);
			swap(&heap->heap[cur], &heap->heap[min]);
			cur = min;
			left = cur * 2;
			right = left + 1;
			continue;
		}
		else {
			break;
		}
	}
	if (left == heap->numNodes) {
		min = left;
		if (priority[heap->heap[cur]] > priority[heap->heap[min]]) {
			swap(&heap->heapMap[heap->heap[cur]], &heap->heapMap[heap->heap[min]]);
			swap(&heap->heap[cur], &heap->heap[min]);
		}
	}
	return returnValue;
}

void decreaseKey(Heap* heap, int node, int* priority) {
	int cur, parent;
	cur = heap->heapMap[node];
	while (cur > 1) {
		parent = cur / 2;
		if (priority[heap->heap[parent]] > priority[node]) {
			swap(&heap->heapMap[heap->heap[parent]], &heap->heapMap[node]);
			swap(&heap->heap[parent], &heap->heap[cur]);
			cur = parent;
			continue;
		}
		else {
			break;
		}
	}
}

int main() {
	int* backtrack;
	int* dist;
	int* route;
	Heap heap;
	heap.numNodes = 0;
	Node* adjList, * nodep;
	int numCity, numBus, count = 0;
	int src, dst, start, end, cost, city;
	scanf("%d %d", &numCity, &numBus);
	dist = (int*)malloc((numCity + 1) * sizeof(int));
	backtrack = (int*)calloc((numCity + 1), sizeof(int));
	heap.heap = (int*)malloc((numCity + 1) * sizeof(int));
	heap.heapMap = (int*)malloc((numCity + 1) * sizeof(int));
	memset(dist, -1, (numCity + 1) * sizeof(int));
	memset(heap.heapMap, -1, (numCity + 1) * sizeof(int));
	adjList = (Node*)calloc(numCity + 1, sizeof(Node));

	int i;
	for (i = 0; i <= numCity; i++) {
		adjList[i].index = i;
		adjList[i].lastNode = &adjList[i];
	}
	for (i = 0; i < numBus; i++) {
		scanf("%d %d %d", &src, &dst, &cost);
		nodep = (Node*)calloc(1, sizeof(Node));
		nodep->index = dst;
		nodep->value = cost;
		adjList[src].lastNode->nextNode = nodep;
		adjList[src].lastNode = nodep;
	}
	scanf("%d %d", &start, &end);
	dist[start] = 0;
	backtrack[start] = start;
	push(&heap, start, dist);

	while (heap.numNodes != 0) {
		src = pop(&heap, dist);
		if (src == end) {
			break;
		}
		nodep = adjList[src].nextNode;
		while (nodep != NULL) {
			dst = nodep->index;
			if (dist[dst] == -1) {
				dist[dst] = dist[src] + nodep->value;
				push(&heap, dst, dist);
				backtrack[dst] = src;
			}
			else if (dist[dst] > dist[src] + nodep->value) {
				dist[dst] = dist[src] + nodep->value;
				decreaseKey(&heap, dst, dist);
				backtrack[dst] = src;
			}
			nodep = nodep->nextNode;
		}
	}

	if (src == end) {
		city = end;
		route = (int*)calloc(numCity, sizeof(int));
		count = 1;
		route[0] = end;
		while (city != start) {
			route[count] = backtrack[city];
			count++;
			city = backtrack[city];
		}
		printf("%d\n%d\n", dist[end], count);
		for (i = count - 1; i >= 0; i--) {
			printf("%d", route[i]);
			if (i != 0) {
				printf(" ");
			}
		}
	}
	else {
		for (i = 0; i < 5135312; i++) {
			printf("*\n");
		}
	}
	return 0;
}