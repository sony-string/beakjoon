#include <stdio.h>
#include <stdlib.h>

#ifndef INT_MAX
#define INT_MAX 2147483600
#endif


int main() {
	int** costTable;
	int** houses;
	int numHouses, min;

	scanf("%d", &numHouses);
	int i, k, r;
	houses = (int**)malloc(numHouses * sizeof(int*));
	costTable = (int**)malloc(numHouses * sizeof(int*));

	for (i = 0; i < numHouses; i++) {
		houses[i] = (int*)malloc(3 * sizeof(int));
		costTable[i] = (int*)malloc(3 * sizeof(int));
		scanf("%d %d %d", &houses[i][0], &houses[i][1], &houses[i][2]);
	}
	costTable[0][0] = houses[0][0];
	costTable[0][1] = houses[0][1];
	costTable[0][2] = houses[0][2];
	for (i = 1; i < numHouses; i++) {
		for (k = 0; k < 3; k++) {
			min = INT_MAX;
			for (r = 0; r < 3; r++) {
				if (r == k) {
					continue;
				}
				if (costTable[i - 1][r] < min) {
					min = costTable[i - 1][r];
				}
			}
			costTable[i][k] = min + houses[i][k];
		}
	}
	min = costTable[numHouses - 1][0];
	if (costTable[numHouses - 1][1] < min) {
		min = costTable[numHouses - 1][1];
	}
	if (costTable[numHouses - 1][2] < min) {
		min = costTable[numHouses - 1][2];
	}
	printf("%d", min);

	for (i = 0; i < numHouses; i++) {
		free(costTable[i]);
		free(houses[i]);
	}
	free(costTable);
	free(houses);
	return 0;
}