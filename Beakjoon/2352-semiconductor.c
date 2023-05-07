#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int findPlace(int* arr, int size, int item) {
	int m, l = 0, r = size - 1;
	while (l <= r) {
		m = l + r;
		m /= 2;
		if (arr[m] < item) {
			l = m + 1;
			continue;
		}
		else {
			r = m - 1;
			continue;
		}
	}
	if (l == m + 1) {
		return l;
	}
	else {
		return m;
	}
}

int main() {
	int* arr;
	int* table;
	int size, top, index;
	scanf("%d", &size);
	arr = (int*)malloc(size * sizeof(int));
	table = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++) {
		scanf("%d", &arr[i]);
	}
	top = 0;
	table[top] = arr[0];
	top++;
	for (int i = 1; i < size; i++) {
		index = findPlace(table, top, arr[i]);
		if (index == top) {
			top++;
			table[index] = arr[i];
		}
		else if (table[index] > arr[i]) {
			table[index] = arr[i];
		}
	}
	printf("%d", top);
	return 0;
}