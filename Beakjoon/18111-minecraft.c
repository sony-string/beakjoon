#include <stdio.h>
#include <stdlib.h>

int main() {
	int groundLevel, numBlocks, bestLevel, bestTime, time, neededBlock;
	int i, N, M, area, minLevel, maxLevel;
	int* arr;

	scanf("%d %d %d", &N, &M, &numBlocks);
	area = N * M;
	arr = (int*)malloc(area * sizeof(int));
	minLevel = 256; maxLevel = 0;
	for (i = 0; i < area; i++) {
		scanf("%d", &arr[i]);
		if (minLevel > arr[i])
			minLevel = arr[i];
		if (maxLevel < arr[i])
			maxLevel = arr[i];
	}
	bestTime = 2147483600;
	for (groundLevel = minLevel; groundLevel <= maxLevel; groundLevel++) {
		time = 0; neededBlock = 0;
		for (i = 0; i < area; i++) {
			neededBlock += groundLevel - arr[i];
			if (groundLevel - arr[i] > 0)
				time += groundLevel-arr[i];
			else if (groundLevel - arr[i] < 0)
				time += 2*(arr[i]-groundLevel);
		}
		if (bestTime >= time && neededBlock <= numBlocks) {
			bestTime = time;
			bestLevel = groundLevel;
		}
	}
	printf("%d %d", bestTime, bestLevel);
	free(arr);
	return 0;
}