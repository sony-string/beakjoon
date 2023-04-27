#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main() {
	int* arr, ** spTmin, **spTmax;
	int sizeArr, numQuery, logSize, l, r, min, max, len;
	scanf("%d %d", &sizeArr, &numQuery);
	arr = (int*)calloc(sizeArr, sizeof(int));
	spTmin = (int**)calloc(sizeArr, sizeof(int*));
	spTmax = (int**)calloc(sizeArr, sizeof(int*));
	logSize = (int)floor(log2((double)sizeArr));
	int i, k;
	for (i = 0; i < sizeArr; i++) {
		scanf("%d", &arr[i]);
		spTmin[i] = (int*)calloc(logSize, sizeof(int));
		spTmax[i] = (int*)calloc(logSize, sizeof(int));
	}
	for (i = 0; i < sizeArr; i++) {
		spTmin[i][0] = i;
		spTmax[i][0] = i;
	}
	for (k = 1; k <= logSize; k++) {
		for (i = 0; i + (1 << k) - 1 < sizeArr; i++) {
			if (arr[spTmin[i][k - 1]] < arr[spTmin[i + (1 << (k - 1))][k - 1]]) {
				spTmin[i][k] = spTmin[i][k - 1];
			}
			else {
				spTmin[i][k] = spTmin[i + (1 << (k - 1))][k - 1];
			}

			if (arr[spTmax[i][k - 1]] > arr[spTmax[i + (1 << (k - 1))][k - 1]]) {
				spTmax[i][k] = spTmax[i][k - 1];
			}
			else {
				spTmax[i][k] = spTmax[i + (1 << (k - 1))][k - 1];
			}
		}
	}

	for (i = 0; i < numQuery; i++) {
		scanf("%d %d", &l, &r);
		l--; r--;
		if (l > r) {
			swap(&l, &r);
		}
		len = (int)floor(log2((double)(r - l + 1)));
		min = arr[spTmin[l][len]] < arr[spTmin[r - (1 << len) + 1][len]] ? 
			arr[spTmin[l][len]] : arr[spTmin[r - (1 << len) + 1][len]];
		max = arr[spTmax[l][len]] > arr[spTmax[r - (1 << len) + 1][len]] ? 
			arr[spTmax[l][len]] : arr[spTmax[r - (1 << len) + 1][len]];
		printf("%d %d\n", min, max);
	}

	return 0;
}