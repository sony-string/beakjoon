#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
	int* l = *((int*)a);
	int* r = *((int*)b);
	if (l[1] > r[1]) {
		return 1;
	}
	else if (l[1] == r[1]) {
		if (l[0] > r[0]) {
			return -1;
		}
		else {
			return 1;
		}
	}
	else {
		return -1;
	}
}

int main() {
	int** arr;
	int numMeats, goal, sum, pay, best;
	scanf("%d %d", &numMeats, &goal);
	
	arr = (int**)malloc(numMeats * sizeof(int*));
	for (int i = 0; i < numMeats; i++) {
		arr[i] = (int*)malloc(2 * sizeof(int));
		scanf("%d %d", arr[i], arr[i] + 1);
	}
	qsort(arr, numMeats, sizeof(int*), &compare);
	
	sum = 0;
	pay = 0;
	sum += arr[0][0];
	pay += arr[0][1];
	best = 2147483647;
	for (int i = 1; i < numMeats; i++) {
		if (arr[i - 1][1] == arr[i][1]) {
			sum += arr[i][0];
			pay += arr[i][1];
			if (sum >= goal) {
				best = pay < best ? pay : best;
			}
			continue;
		}
		pay = arr[i][1];
		sum += arr[i][0];
		if (sum >= goal) {
			best = best < pay ? best : pay;
			break;
		}
	}
	if (sum >= goal) {
		printf("%d", best);
	}
	else {
		printf("-1");
	}
	return 0;
}