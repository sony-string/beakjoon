#include <stdio.h>
#include <stdlib.h>

void sort(int**, int, int);

int main() {
	int numberOfLines;
	scanf("%d", &numberOfLines);
	int** arr = (int**)malloc(numberOfLines * sizeof(int*));
	int i, result = 0;

	for (i = 0; i < numberOfLines; i++) {
		arr[i] = (int*)malloc(2 * sizeof(int));
		scanf("%d", &arr[i][0]);
		arr[i][1] = i;
	}
	sort(arr, 0, numberOfLines - 1);

	for (i = 0; i < numberOfLines; i++) {
		if (arr[i][1] - i > result) {
			result = arr[i][1] - i;
		}
	}
	result++;
	printf("%d", result);

	for (i = 0; i < numberOfLines; i++) {
		free(arr[i]);
	}
	free(arr);
	return 0;
}

void merge(int** arr, int s, int m, int l) {
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

void sort(int** arr, int s, int l) {
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
