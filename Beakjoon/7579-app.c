#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int numApps, neededMem, result = 10001;
	scanf("%d %d", &numApps, &neededMem);
	int* arr = (int*)malloc(numApps * sizeof(int));
	int* arrCost = (int*)malloc(numApps * sizeof(int));
	int** table = (int**)malloc(numApps * sizeof(int*));
	int i, k;
	int sumMem = 0, sumCost = 0, l = 0, r = -1;

	for (i = 0; i < numApps; i++) {
		table[i] = (int*)calloc(numApps * 100 + 1, sizeof(int));
		memset(table[i], 255, ((numApps * 100) + 1) * sizeof(int));
		table[i][0] = 0;
		scanf("%d", &arr[i]);
	}
	for (i = 0; i < numApps; i++) {
		scanf("%d", &arrCost[i]);
	}

	table[0][arrCost[0]] = arr[0];
	if (arr[0] >= neededMem) {
		result = arrCost[0];
	}
	for (i = 1; i < numApps; i++) {
		for (k = 0; k <= numApps * 100; k++) {
			table[i][k] = table[i - 1][k];
		}
		for (k = 0; k <= numApps * 100 - arrCost[i]; k++) {
			if (table[i - 1][k] == -1) {
				continue;
			}
			if (table[i - 1][k] < neededMem && table[i - 1][k] + arr[i] > table[i][k + arrCost[i]]) {
				table[i][k + arrCost[i]] = table[i - 1][k] + arr[i];
				if (table[i][k + arrCost[i]] >= neededMem) {
					if (k + arrCost[i] < result) {
						result = k + arrCost[i];
					}
				}
			}
		}
	}

	printf("%d", result);

	for (i = 0; i < numApps; i++) {
		free(table[i]);
	}
	free(table);
	free(arr);
	free(arrCost);
	return 0;
}