#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
	int numNodes;
	int* heap;
} Heap;

void createHeap(Heap* heap) {
	heap->numNodes = 0;
	heap->heap = (int*)malloc(300000 * sizeof(int));
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

//return its item of max value
int pop(Heap* heap) {
	if (heap->numNodes == 0) {
		return -1;
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
void push(Heap* heap, int item) {
	heap->heap[heap->numNodes] = item;
	int parent, index;
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


void mergeJuwels(int** arr, int s, int m, int l) {
	int size = l - s + 1;
	if (size != 1) {
		int i = s, j = m + 1, k = 0;
		int** sorted = (int**)malloc(size * sizeof(int*));
		int temp;
		for (temp = 0; temp < size; temp++) {
			sorted[temp] = (int*)malloc(2 * sizeof(int));
		}
		while (i <= m && j <= l) {
			if (arr[i][0] <= arr[j][0]) {
				sorted[k][0] = arr[i][0];
				sorted[k][1] = arr[i][1];
				i++; k++;
				continue;
			}
			sorted[k][0] = arr[j][0];
			sorted[k][1] = arr[j][1];
			j++; k++;
		}

		if (i <= m) {
			while (k < size) {
				sorted[k][0] = arr[i][0];
				sorted[k][1] = arr[i][1];
				k++; i++;
			}
		}
		else {
			while (k < size) {
				sorted[k][0] = arr[j][0];
				sorted[k][1] = arr[j][1];
				k++; j++;
			}
		}
		for (i = 0; i < size; i++) {
			arr[i + s][0] = sorted[i][0];
			arr[i + s][1] = sorted[i][1];
		}
		for (temp = 0; temp < size; temp++) {
			free(sorted[temp]);
		}
		free(sorted);
	}
}

void sortJuwels(int** arr, int s, int l) {
	int m = (s + l) / 2;
	if (m - s == 0) {
		mergeJuwels(arr, s, m, l);
	}
	else {
		sortJuwels(arr, s, m);
		sortJuwels(arr, m + 1, l);
		mergeJuwels(arr, s, m, l);
	}
}

void merge(int* arr, int s, int m, int l) {
	int size = l - s + 1;
	if (size != 1) {
		int i = s, j = m + 1, k = 0;
		int* sorted = (int*)malloc(size * sizeof(int));
		while (i <= m && j <= l) {
			if (arr[i] <= arr[j]) {
				sorted[k] = arr[i];
				i++; k++;
			}
			else {
				sorted[k] = arr[j];
				j++; k++;
			}
		}
		if (i <= m) {
			while (k < size) {
				sorted[k] = arr[i];
				k++; i++;
			}
		}
		else {
			while (k < size) {
				sorted[k] = arr[j];
				k++; j++;
			}
		}
		for (i = 0; i < size; i++) {
			arr[i + s] = sorted[i];
		}
		free(sorted);
	}
}

void sort(int* arr, int s, int l) {
	int m = (s + l) / 2;
	if (m - s == 0) {
		merge(arr, s, m, l);
	}
	else {
		sort(arr, s, m);
		sort(arr, m + 1, l);
		merge(arr, s, m, l);
	}
}

int main() {
	int numJuwels, numBackpacks, temp;
	unsigned long long sum = 0;
	int* backpacks, ** juwels;
	Heap mostValue;
	createHeap(&mostValue);
	int i, point = 0;

	scanf("%d %d", &numJuwels, &numBackpacks);
	juwels = (int**)malloc(numJuwels * sizeof(int*));
	backpacks = (int*)malloc(numBackpacks * sizeof(int));

	for (i = 0; i < numJuwels; i++) {
		juwels[i] = (int*)malloc(2 * sizeof(int));
		scanf("%d %d", &juwels[i][0], &juwels[i][1]);
	}
	for (i = 0; i < numBackpacks; i++) {
		scanf("%d", &backpacks[i]);
	}

	sort(backpacks, 0, numBackpacks - 1);
	sortJuwels(juwels, 0, numJuwels - 1);

	for (i = 0; i < numBackpacks; i++) {
		while (point < numJuwels && juwels[point][0] <= backpacks[i]) {
			push(&mostValue, juwels[point][1]);
			point++;
		}
		temp = pop(&mostValue);
		if (temp == -1) {
			continue;
		}
		sum += temp;
	}

	printf("%llu", sum);

	free(backpacks);
	for (i = 0; i < numJuwels; i++) {
		free(juwels[i]);
	}
	free(juwels);
	free(mostValue.heap);
	return 0;
}