#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int numJobs, numPreJobs;
	int* workTimes;
	int** preOrders;
	int result;
	int num, last;

	scanf("%d", &numJobs);
	workTimes = (int*)calloc(numJobs + 1, sizeof(int));
	preOrders = (int**)calloc(numJobs + 1, sizeof(int*));
	for (int i = 1; i <= numJobs; i++) {
		scanf("%d", workTimes + i);
		scanf("%d", &numPreJobs);
		preOrders[i] = (int*)calloc(numPreJobs + 1, sizeof(int));
		preOrders[i][0] = numPreJobs;
		for (int k = 1; k <= numPreJobs; k++) {
			scanf("%d", preOrders[i] + k);
		}
	}

	result = 0;
	for (int i = 1; i <= numJobs; i++) {
		numPreJobs = preOrders[i][0];
		last = 0;
		for (int k = 1; k <= numPreJobs; k++) {
			num = workTimes[preOrders[i][k]];
			if (num > last) {
				last = num;
			}
		}
		workTimes[i] += last;
		if (workTimes[i] > result) {
			result = workTimes[i];
		}
	}
	printf("%d", result);
	return 0;
}