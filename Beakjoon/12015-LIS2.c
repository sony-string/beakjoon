#include <stdio.h>
#include <stdlib.h>

//return index of num or smaller and closest to num : decreasing sorted array
int bSearch (int* arr, int num, int l, int r) {
	int m;
	while (r >= l) {
		m = (r + l) / 2;
		if (arr[m] < num) {
			r = m - 1;
			continue;
		}
		if (arr[m] > num) {
			l = m + 1;
			continue;
		}
		if (arr[m] == num) {
			break;
		}
	}
	if (arr[m] == num) {
		return m;
	}
	if (r == m - 1) {
		return m;
	}
	if (l == m + 1) {
		return l;
	}
}

int main() {
	int numN, result = 0, index, num;
	int* array;
	FILE* fp = freopen("input.txt", "r", stdin);/********/
	scanf("%d", &numN);
	array = (int*)malloc(numN * sizeof(int));
	int* table = (int*)calloc(numN, sizeof(int));
	int i;
	for (i = 0; i < numN; i++) {
		scanf("%d", &array[i]);
	}
	table[result] = array[numN - 1];
	result++;
	for (i = numN - 2; i >= 0; i--) {
		num = array[i];
		index = bSearch(table, num, 0, result - 1);
		if (table[index] == num) {
			continue;
		}
		if (index == 0) {
			table[0] = num;
		}
		else if (index == result) {
			table[index] = num;
			result++;
		}
		else {
			table[index] = num;
		}
	}
	fclose(fp); /******************/
	printf("%d", result);
	free(array);
	free(table);
	return 0;
}