#include <stdio.h>
#include <stdlib.h>

#define MIN

int main() {
	unsigned long long* stackOfFlagged, * set;
	int size, goalNum, sizeOfSet, zero = 0, numFlagged, flag = 0;
	unsigned long long count = 0;
	int* arr, * flagged;
	scanf("%d %d", &size, &goalNum);
	arr = (int*)malloc(size * sizeof(int));
	set = (unsigned long long*)calloc(8000001, sizeof(unsigned long long));
	int i, k;
	for (i = 0; i < size; i++) {
		scanf("%d", &arr[i]);
	}
	goalNum += 4000000;
	set[arr[0] + 4000000]++;
	set[4000000]++;
	if (arr[0] + 4000000 == goalNum) {
		count++;
	}
	if (arr[0] != 0) {
		sizeOfSet = 2;
	}
	else {
		sizeOfSet = 1;
	}

	for (i = 1; i < size; i++) {
		numFlagged = 0;
		flagged = (int*)calloc(sizeOfSet, sizeof(int));
		stackOfFlagged = (unsigned long long*)calloc(sizeOfSet, sizeof(unsigned long long));

		for (k = 0; k <= 8000000; k++) {
			if (set[k] == 0) {
				continue;
			}
			if (k + arr[i] < 0 || k + arr[i] > 8000000) {
				continue;
			}
			if (k + arr[i] == goalNum) {
				count += set[k];
			}
			if (set[k + arr[i]] == 0) {
				sizeOfSet++;
			}
			flagged[numFlagged] = k + arr[i];
			stackOfFlagged[numFlagged] = set[k];
			numFlagged++;
		}

		for (k = 0; k < numFlagged; k++) {
			set[flagged[k]] += stackOfFlagged[k];
		}

		free(flagged);
		free(stackOfFlagged);
	}
	printf("%llu", count);
	return 0;
}