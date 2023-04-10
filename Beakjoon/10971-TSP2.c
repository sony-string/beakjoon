#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INT_MAX
#define INT_MAX 2147483600
#endif

int travelling(int* visited, int total, int nowPos, int startPos, const int** costs, int numCities) {
	int* _visited = (int*)malloc(numCities * sizeof(int));
	memcpy(_visited, visited, numCities * sizeof(int));
	_visited[nowPos] = 1;
	int i, count = 0, result = INT_MAX, temp;
	for (i = 0; i < numCities; i++) {
		if (_visited[i] != 1 && i != startPos) {
			if (costs[nowPos][i] != 0) {
				temp = travelling(_visited, total + costs[nowPos][i], i, startPos, costs, numCities);
				if (temp < result) {
					result = temp;
				}
				count++;
			}
		}
	}
	if (count == 0) {
		if (costs[nowPos][startPos] == 0) {
			return INT_MAX;
		}
		_visited[startPos] = 1;
		for (i = 0; i < numCities; i++) {
			if (_visited[i] == 0) {
				return INT_MAX;
			}
		}
		return total + costs[nowPos][startPos];
	}
	free(_visited);
	return result;
}

int main() {
	int* visited;
	int** costs;
	int cost, temp, result = INT_MAX;
	int numCities;
	scanf("%d", &numCities);

	int i, k;
	costs = (int**)malloc(numCities * sizeof(int*));
	visited = (int*)calloc(numCities, sizeof(int));
	for (i = 0; i < numCities; i++) {
		costs[i] = (int*)malloc(numCities * sizeof(int));
		for (k = 0; k < numCities; k++) {
			scanf("%d", &cost);
			costs[i][k] = cost;
		}
	}

	for (i = 0; i < numCities; i++) {
		for (k = 0; k < numCities; k++) {
			if (costs[i][k] != 0) {
				temp = travelling(visited, costs[i][k], k, i, costs, numCities);
				if (temp < result) {
					result = temp;
				}
			}
		}
	}
	printf("%d", result);
	
	for (i = 0; i < numCities; i++) {
		free(costs[i]);
	}
	free(costs);
	free(visited);
	return 0;
}