#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

int solve(int** table, int** matrix, int start, int end) {
	int result, i, best = INT_MAX;

	if (end - start > 1) {
		for (i = start; i < end; i++) {
			if (table[start][i] == -1) {
				table[start][i] = solve(table, matrix, start, i);
			}
			if (table[i + 1][end] == -1) {
				table[i + 1][end] = solve(table, matrix, i + 1, end);
			}
			result = table[start][i] + table[i + 1][end] + matrix[start][0] * matrix[i][1] * matrix[end][1];
			if (result < best) {
				best = result;
			}
		}
		return best;
	}
	if (end == start) {
		return 0;
	}
	return matrix[start][0] * matrix[start][1] * matrix[end][1];
}

int main() {
	int** matrix, ** table;
	int numMatrix, result;
	scanf("%d", &numMatrix);
	matrix = (int**)malloc(numMatrix * sizeof(int*));
	table = (int**)malloc(numMatrix * sizeof(int*));

	int i;
	for (i = 0; i < numMatrix; i++) {
		matrix[i] = (int*)malloc(2 * sizeof(int));
		table[i] = (int*)malloc(numMatrix * sizeof(int));
		memset(table[i], 255, numMatrix * sizeof(int));;
		scanf("%d %d", &matrix[i][0], &matrix[i][1]);
	}
	result = solve(table, matrix, 0, numMatrix - 1);
	printf("%d", result);
	
	return 0;
}