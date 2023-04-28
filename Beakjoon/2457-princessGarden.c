#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int** arr, int l, int m, int r) {
	int** sorted = (int**)calloc(r - l + 1, sizeof(int*));
	int i, k = 0;
	int left = l, right = m;
	while (left < m && right <= r) {
		if (arr[left][0] < arr[right][0]) {
			sorted[k] = arr[left];
			left++;
			k++;
		}
		else {
			sorted[k] = arr[right];
			right++;
			k++;
		}
	}
	while (left < m) {
		sorted[k] = arr[left];
		left++;
		k++;
	}
	while (right <= r) {
		sorted[k] = arr[right];
		right++;
		k++;
	}
	k = 0;
	for (i = l; i <= r; i++) {
		arr[i] = sorted[k];
		k++;
	}
	free(sorted);
}

void mergeSort(int** arr, int l, int r) {
	int m = (l + r) / 2;
	if (r - l != 0) {
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
	}
	merge(arr, l, m + 1, r);
}

int main() {
	int START_DAY = 59, END_DAY = 333;
	int term = END_DAY - START_DAY + 1;
	int daysPerMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int numFlowers;
	int month, day, index = -1;
	int result = 0;
	scanf("%d", &numFlowers);
	int** flowerInfo = (int**)calloc(numFlowers, sizeof(int*));
	int i, k;
	int l = 0, r = 0;
	for (i = 0; i < numFlowers; i++) {
		flowerInfo[i] = (int*)calloc(2, sizeof(int));
		scanf("%d %d", &month, &day);
		for (k = 0; k < month - 1; k++) {
			day += daysPerMonth[k];
		}
		day -= 1;
		flowerInfo[i][0] = day;
		scanf("%d %d", &month, &day);
		for (k = 0; k < month - 1; k++) {
			day += daysPerMonth[k];
		}
		day -= 2;
		flowerInfo[i][1] = day;
	}
	mergeSort(flowerInfo, 0, numFlowers - 1);
	k = 0;
	for (i = START_DAY; i <= END_DAY;) {
		result++;
		index = -1;
		for (; k < numFlowers; k++) {
			if (flowerInfo[k][0] <= i && flowerInfo[k][1] >= i) {
				if (index == -1) {
					index = k;
				}
				else {
					if (flowerInfo[index][1] < flowerInfo[k][1]) {
						index = k;
					}
				}
			}
			else if (flowerInfo[k][0] > i) {
				break;
			}
		}
		if (index != -1) {
			i = flowerInfo[index][1] + 1;
		}
		else {
			break;
		}
	}
	if (index == -1) {
		printf("0");
	}
	else {
		printf("%d", result);
	}
	return 0;
}