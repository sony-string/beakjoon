#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(long long* arr, int l, int r) {
	long long* sorted;
	int size = r - l + 1;
	int i, j, k, m;
	m = l + r;
	m /= 2;
	i = l; j = m + 1;
	k = 0;
	sorted = (long long*)malloc(size * sizeof(long long));
	while (i <= m && j <= r) {
		if (arr[i] <= arr[j]) {
			sorted[k] = arr[i];
			i++;
			k++;
		}
		else {
			sorted[k] = arr[j];
			j++;
			k++;
		}
	}
	while (i <= m) {
		sorted[k] = arr[i];
		i++;
		k++;
	}
	while (j <= r) {
		sorted[k] = arr[j];
		j++;
		k++;
	}
	k = 0;
	for (i = l; i <= r; i++) {
		arr[i] = sorted[k];
		k++;
	}
	free(sorted);
}

void mergeSort(long long* arr, int l, int r) {
	if (r != l) {
		int m;
		m = r + l;
		m /= 2;
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
		merge(arr, l, r);
	}
}


int main() {
	long long find, * arr, * newArr;
	int size, newSize, best;
	int i, j, k, r, m, l;
	scanf("%d", &size);
	newSize = (size * (size + 1)) / 2;
	arr = (long long*)malloc(size * sizeof(long long));
	newArr = (long long*)malloc(newSize * sizeof(long long));
	for (i = 0; i < size; i++) {
		scanf("%lld", arr + i);
	}
	r = 0;
	for (i = 0; i < size; i++) {
		for (k = i; k < size; k++) {
			newArr[r] = arr[i] + arr[k];
			r++;
		}
	}
	mergeSort(arr, 0, size - 1);
	mergeSort(newArr, 0, newSize - 1);

	find = -1; m = 0; best = 0;
	for (i = size - 1; i >= 0; i--) {
		for (j = 0; j < i; j++) {
			find = arr[i] - arr[j];
			l = 0; r = newSize - 1;
			while (r >= l) {
				m = r + l;
				m /= 2;
				if (newArr[m] == find) {
					break;
				}
				else if (newArr[m] < find) {
					l = m + 1;
					continue;
				}
				else {
					r = m - 1;
				}
			}
			if (newArr[m] == find) {
				break;
			}
		}
		if (newArr[m] == find) {
			break;
		}
	}

	printf("%lld", arr[i]);
	return 0;
}