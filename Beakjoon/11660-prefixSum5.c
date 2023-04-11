#include <stdio.h>
#include <stdlib.h>

int main() {
	int size, testCases, sum;
	int x1, x2, y1, y2;
	int** arr, ** sumTable;
	
	scanf("%d %d", &size, &testCases);
	int i, k, T;
	arr = (int**)malloc(size * sizeof(int*));
	sumTable = (int**)malloc(size * sizeof(int*));
	for (i = 0; i < size; i++) {
		arr[i] = (int*)malloc(size * sizeof(int));
		sumTable[i] = (int*)calloc(size, sizeof(int));
		scanf("%d", &arr[i][0]);
		sumTable[i][0] = arr[i][0];
		for (k = 1; k < size; k++) {
			scanf("%d", &arr[i][k]);
			sumTable[i][k] = sumTable[i][k - 1] + arr[i][k];
		}
		if (i != 0) {
			for (k = 0; k < size; k++) {
				sumTable[i][k] += sumTable[i - 1][k];
			}
		}
	}
	/*
	for (i = 0; i < size; i++) {
		for (k = 0; k < size; k++) {
			printf("%d ", sumTable[i][k]);
		}
		printf("\n");
	}
	printf("****\n");
	*/
	for (T = 0; T < testCases; T++) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		x1--; y1--; x2--; y2--;
		sum = sumTable[x2][y2];
		if (x1 != 0) {
			sum -= sumTable[x1 - 1][y2];
		}
		if (y1 != 0) {
			sum -= sumTable[x2][y1 - 1];
		}
		if (x1 != 0 && y1 != 0) {
			sum += sumTable[x1 - 1][y1 - 1];
		}
		printf("%d\n", sum);
	}

	for (i = 0; i < size; i++) {
		free(sumTable[i]);
		free(arr[i]);
	}
	free(sumTable);
	free(arr);
	return 0;
}