#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int numDays;
	int period;
	int best;
	int bestCount;
	int sum;
	int* visitCounts;
	int start, end;

	scanf("%d %d", &numDays, &period);
	visitCounts = (int*)malloc(numDays * sizeof(int));
	for (int i = 0; i < numDays; i++) {
		scanf("%d", visitCounts + i);
	}
	start = 0;
	sum = 0;
	for (end = 0; end < period; end++) {
		sum += visitCounts[end];
	}
	best = sum;
	bestCount = 1;

	for (; end < numDays; end++) {
		sum -= visitCounts[start];
		start++;
		sum += visitCounts[end];
		if (sum > best) {
			best = sum;
			bestCount = 1;
			continue;
		}
		else if (sum == best) {
			bestCount++;
		}
	}
	if (best > 0) {
		printf("%d\n%d", best, bestCount);
	}
	else {
		printf("SAD");
	}
	return 0;
}