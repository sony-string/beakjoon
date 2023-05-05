#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	int** map, ** table;
	int row, col, sum;
	scanf("%d %d", &row, &col);
	map = (int**)malloc(row * sizeof(int*));
	table = (int**)malloc(row * sizeof(int*));
	for (int i = 0; i < row; i++) {
		map[i] = (int*)malloc(col * sizeof(int));
		table[i] = (int*)malloc(col * sizeof(int));
		for (int j = 0; j < col; j++) {
			scanf("%d", &map[i][j]);
			table[i][j] = -1000000000;
		}
	}
	if (row == 1) {
		sum = 0;
		for (int i = 0; i < col; i++) {
			sum += map[0][i];
		}
		printf("%d", sum);
		return 0;
	}
	table[0][0] = map[0][0];
	table[1][0] = table[0][0] + map[1][0];
	for (int i = 1; i < col; i++) {
		table[0][i] = table[0][i - 1] + map[0][i];
		table[1][i] = table[0][i] + map[1][i];
	}

	for (int i = 1; i < row - 1; i++) {
		for (int j = 0; j < col; j++) {
			sum = table[i][j];
			for (int k = j - 1; k >= 0; k--) {
				sum += map[i][k];
				if (table[i + 1][k] < sum + map[i + 1][k]) {
					table[i + 1][k] = sum + map[i + 1][k];
				}
			}
			sum = table[i][j];
			for (int k = j + 1; k < col; k++) {
				sum += map[i][k];
				if (table[i + 1][k] < sum + map[i + 1][k]) {
					table[i + 1][k] = sum + map[i + 1][k];
				}
			}
			if (table[i + 1][j] < table[i][j] + map[i + 1][j]) {
				table[i + 1][j] = table[i][j] + map[i + 1][j];
			}
		}
	}
	for (int i = 0; i < col - 1; i++) {
		sum = table[row - 1][i];
		for (int j = i + 1; j < col; j++) {
			sum += map[row - 1][j];
		}
		if (sum > table[row - 1][col - 1]) {
			table[row - 1][col - 1] = sum;
		}
	}

	printf("%d", table[row - 1][col - 1]);
	return 0;
}