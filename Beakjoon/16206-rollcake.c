#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
	int l = *((int*)a);
	int r = *((int*)b);
	if (l % 10 == r % 10 && l % 10 == 0) {
		if (l > r) {
			return 1;
		}
		else if (l == r) {
			return 0;
		}
		else {
			return -1;
		}
	}
	else if (l % 10 == 0 || r % 10 == 0) {
		if (r % 10 == 0) {
			return 1;
		}
		else {
			return -1;
		}
	}
	else {
		if (l > r) {
			return -1;
		}
		else {
			return 1;
		}
	}
}

int main() {
	int top;
	int* arr;
	int numCakes;
	int totalScore;
	int score;
	int cutCount;

	scanf("%d %d", &numCakes, &cutCount);
	arr = (int*)malloc(numCakes * sizeof(int));
	top = 0;
	for (int i = 0; i < numCakes; i++) {
		scanf("%d", arr + i);
	}
	qsort(arr, numCakes, sizeof(int), compare);

	totalScore = 0;
	while (cutCount > 0 && top < numCakes) {
		if (arr[top] == 10) {
			totalScore++;
			top++;
			continue;
		}
		else if (arr[top] % 10 == 0) {
			if (cutCount >= (arr[top] / 10) - 1) {
				cutCount -= (arr[top] / 10) - 1;
				totalScore += (arr[top] / 10);
				top++;
				continue;
			}
			else {
				totalScore += cutCount;
				cutCount = 0;
				break;
			}
		}
		else if (arr[top] > 10) {
			score = arr[top] / 10;
			if (score > cutCount) {
				totalScore += cutCount;
				cutCount = 0;
				break;
			}
			else {
				cutCount -= score;
				totalScore += score;
				top++;
				continue;
			}
		}
		else {
			break;
		}
	}
	printf("%d", totalScore);
	return 0;
}