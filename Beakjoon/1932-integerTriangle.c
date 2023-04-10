#include <stdio.h>
#include <stdlib.h>

int main() {
	int size, numIntegers, level = 0, max;
	int* firstIndexOfLevel, * triangle;
	scanf("%d", &size);
	firstIndexOfLevel = (int*)malloc(size * sizeof(int));
	numIntegers = (size * (size + 1)) / 2;
	triangle = (int*)malloc(numIntegers * sizeof(int));

	int i, k, index;
	firstIndexOfLevel[0] = 0;
	for (i = 1; i < size; i++) {
		firstIndexOfLevel[i] = i * (i + 1) / 2;
	}
	for (i = 0; i < numIntegers; i++) {
		scanf("%d", &triangle[i]);
	}
	for (i = 1; i < size; i++) {
		level++;
		index = firstIndexOfLevel[level];
		for (k = 0; k < level + 1; k++) {
			if (k == 0) {
				max = triangle[firstIndexOfLevel[level - 1] + k];
			}
			else if (k == level) {
				max = triangle[firstIndexOfLevel[level - 1] + k - 1];
			}
			else {
				max = triangle[firstIndexOfLevel[level - 1] + k - 1];
				if (max < triangle[firstIndexOfLevel[level - 1] + k]) {
					max = triangle[firstIndexOfLevel[level - 1] + k];
				}
			}
			triangle[index + k] += max;
		}
	}
	max = triangle[firstIndexOfLevel[size - 1]];
	for (i = firstIndexOfLevel[size - 1] + 1; i < numIntegers; i++) {
		if (max < triangle[i]) {
			max = triangle[i];
		}
	}
	printf("%d", max);

	free(firstIndexOfLevel);
	free(triangle);
	return 0;
}