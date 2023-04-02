#include <stdio.h>
#include <stdlib.h>

int getArray(int *arr, int numN, int numSelect, int start, int M) {
	int i;
	if (numSelect == 0) {
		for (i = 0; i < M; i++) {
			printf("%d ", arr[i]);
		}
		printf("\n");
		return 0;
	}

	for (i = start; i <= numN - numSelect + 1; i++) {
		arr[M - numSelect] = i;
		getArray(arr, numN, numSelect - 1, i + 1, M);
	}
	return 0;
}

int main() {
	int numN, numSelect;
	scanf("%d %d", &numN, &numSelect);
	int* arr = (int*)malloc((numSelect + 1) * sizeof(int));
	getArray(arr, numN, numSelect, 1, numSelect);
	free(arr);
	return 0;
}