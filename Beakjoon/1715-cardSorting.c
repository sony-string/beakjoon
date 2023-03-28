#include <stdio.h>
#include <stdlib.h>

void sort(int*, int, int);
void swap(int*, int*);
void sortElement(int*, int, int);

int main() {
	int sum, i, size;
	int* arr;

	scanf("%d", &size);
	arr = (int*)malloc(size * sizeof(int));
	for (i = 0; i < size; i++) {
		scanf("%d", &arr[i]);
	}

	sum = 0;
	if (size > 2) {
		sort(arr,0,size-1);
		for (i = 0; i < size - 1; i++) {
			//printf("%d + %d = %d\n", arr[i], arr[i + 1], arr[i] + arr[i + 1]);
			sum += arr[i] + arr[i + 1];
			arr[i+1] += arr[i];
			sortElement(&arr[i + 1], 0,size-i-1);
		}
	}
	else {
		if (size == 2)
			sum = arr[0] + arr[1];
		else if (size == 1)
			sum = 0;
	}
	printf("%d", sum);
	free(arr);
	return 0;
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void insertToTarget(int* arr, int i, int tgt) {
	int j, temp;
	temp = arr[i];
	if (tgt > i) {
		for (j = i; j < tgt; j++) {
			arr[j] = arr[j + 1];
		}
		arr[tgt] = temp;
	}
	else if (tgt < i) {
		for (j = i; j > tgt; j--) {
			arr[j] = arr[j - 1];
		}
		arr[tgt] = temp;
	}
}

void sortElement(int* arr, int i, int size) {
	int l = 0, r = size - 1;
	int m= (r+l)/2;

	while (r > l) {
		if (arr[m] > arr[i])
			r = m - 1;
		else if (arr[m] < arr[i])
			l = m + 1;
		else if (arr[m] == arr[i])
			break;
		m = (r + l) / 2;
	}
	if (m != i) {
		if (arr[m] >= arr[i]) {
			if (m > i)
				insertToTarget(arr, i, m - 1);
			else
				insertToTarget(arr, i, m);
		}
		else {
			if (m > i)
				insertToTarget(arr, i, m);
			else
				insertToTarget(arr, i, m + 1);
		}
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