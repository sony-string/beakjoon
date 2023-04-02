#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int getArray(int* arr, int *numArr, int numSelect, int numN, int M) {
	int i, k;
	if (numSelect == 0) {
		for (i = 0; i < M; i++) {
			printf("%d ", numArr[arr[i]]);
		}
		printf("\n");
		return 0;
	}

	for (i = 0; i < numN; i++) {
		for (k = 0; k < M - numSelect; k++) {
			if (arr[k] == i) {
				break;
			}
		}
		if (k != M - numSelect) {
			continue;
		}
		arr[M - numSelect] = i;
		getArray(arr, numArr, numSelect - 1, numN, M);
	}
	return 0;
}

int main() {
	int numN, numSelect;
	scanf("%d %d", &numN, &numSelect);
	int* numArr = (int*)malloc(numN * sizeof(int));
	int* arr = (int*)malloc((numSelect + 1) * sizeof(int));
	int i, j;
	for (i = 0; i < numN; i++) {
		scanf("%d", &numArr[i]);
	}
	for (i = 0; i < numN - 1; i++) {
		for (j = i + 1; j < numN; j++) {
			if (numArr[i] > numArr[j]) {
				swap(&numArr[i], &numArr[j]);
			}
		}
	}
	getArray(arr, numArr, numSelect, numN, numSelect);
	free(arr);
	return 0;
}