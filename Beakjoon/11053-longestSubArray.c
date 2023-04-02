#include <stdio.h>
#include <stdlib.h>

int main() {
	int numN, result = 0, index;
	int* array;
	scanf("%d", &numN);
	array = (int*)malloc(numN * sizeof(int));
	int* resultFromArr = (int*)malloc(numN * sizeof(int));
	int i;
	for (i = 0; i < numN; i++) {
		scanf("%d", &array[i]);
		resultFromArr[i] = 1;
	}
	result = 1;
	for (i = numN - 2; i >= 0; i--) {
		for (index = i; index <= numN - 1; index++) {
			if (array[index] > array[i] && resultFromArr[i] < resultFromArr[index] + 1) {
				resultFromArr[i] = resultFromArr[index] + 1;
			}
		}
		if (result < resultFromArr[i]) {
			result = resultFromArr[i];
		}
	}
	printf("%d", result);
	free(array);
	free(resultFromArr);
	return 0;
}