#include <stdio.h>
#include <stdlib.h>

#ifndef INT_MIN
#define INT_MIN -2147483600
#endif

int main() {
	int numItems, capacity, result = 0;
	scanf("%d %d", &numItems, &capacity);

	int* weights = (int*)malloc(numItems * sizeof(int));
	int* values = (int*)malloc(numItems * sizeof(int));
	int** states = (int**)malloc(numItems * sizeof(int*));
	int i, k;

	for (i = 0; i < numItems; i++) {
		scanf("%d %d", &weights[i], &values[i]);
		states[i] = (int*)malloc((capacity + 1) * sizeof(int));
		for (k = 0; k <= capacity; k++) {
			states[i][k] = INT_MIN;
		}
		states[i][0] = 0;
	}
	result = 0;
	if (weights[0] <= capacity) {
		states[0][weights[0]] = values[0];
		result = values[0];
	}

	for (i = 1; i < numItems; i++) {
		for (k = 0; k <= capacity; k++) {
			if (states[i][k] < states[i - 1][k]) {
				states[i][k] = states[i - 1][k];
			}
			if (weights[i] + k <= capacity) {
				states[i][k + weights[i]] = states[i - 1][k] + values[i];
				if (states[i][k + weights[i]] > result) {
					result = states[i][k + weights[i]];
				}
			}
		}
	}
	printf("%d", result);

	free(weights);
	free(values);
	for (i = 0; i < numItems; i++) {
		free(states[i]);
	}
	return 0;
}