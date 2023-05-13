#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

enum {
	ballcolor = 0, ballsize = 1
};

int compare(const void* a, const void* b) {
	if (((int**)a)[0][0] > ((int**)b)[0][0]) {
		return 1;
	}
	else if (((int**)a)[0][0] == ((int**)b)[0][0]) {
		return 0;
	}
	else {
		return -1;
	}
}

int main() {
	int prefixSum[2001];
	int arr[2001];
	int** balls;
	int*** colorList;
	int* numEachColor;
	int* answer;
	int numBalls, color, sum, cur, index, result, size;

	scanf("%d", &numBalls);
	memset(arr, 0, sizeof(int[2001]));
	memset(prefixSum, 0, sizeof(int[2001]));
	balls = (int**)malloc(numBalls * sizeof(int*));
	colorList = (int***)malloc((numBalls + 1)* sizeof(int**));
	numEachColor = (int*)calloc(numBalls + 1, sizeof(int));
	answer = (int*)calloc(numBalls, sizeof(int));

	for (int i = 0; i < numBalls; i++) {
		balls[i] = (int*)malloc(2 * sizeof(int));
		scanf("%d %d", balls[i], balls[i] + 1);
		arr[balls[i][ballsize]]++;
		numEachColor[balls[i][ballcolor]] += 1;
	}
	for (int i = 0; i <= numBalls; i++) {
		colorList[i] = (int**)malloc((numEachColor[i] + 1) * sizeof(int*));
		for (int k = 0; k < numEachColor[i] + 1; k++) {
			colorList[i][k] = (int*)malloc(2 * sizeof(int));
		}
		colorList[i][0][0] = 0;
		colorList[i][0][1] = 0;
	}
	for (int i = 0; i < numBalls; i++) {
		color = balls[i][ballcolor];
		colorList[color][0][0]++;
		colorList[color][colorList[color][0][0]][0] = balls[i][ballsize];
		colorList[color][colorList[color][0][0]][1] = i;
	}
	for (int i = 1; i <= numBalls; i++) {
		if (numEachColor[i] > 1) {
			qsort(&colorList[i][1], numEachColor[i], sizeof(int**), &compare);
		}
	}
	/*
	printf("\n");
	for (int i = 0; i <= numBalls; i++) {
		printf("color %d : ", i);
		for (int k = 1; k <= numEachColor[i]; k++) {
			printf("(%d, %d) ", colorList[i][k][0], colorList[i][k][1]);
		}
		printf("\n");
	}
	*/
	for (int i = 1; i <= 2000; i++) {
		prefixSum[i] = prefixSum[i - 1] + arr[i - 1] * (i - 1);
	}
	for (int i = 1; i <= numBalls; i++) {
		if (numEachColor[i] == 0) {
			continue;
		}
		sum = 0;
		for (cur = 1; cur <= numEachColor[i]; cur++) {
			if (cur > 1 && size == colorList[i][cur][0]) {
				sum += size;
				answer[colorList[i][cur][1]] = result;
				continue;
			}
			result = prefixSum[colorList[i][cur][0]];
			result -= sum;
			index = colorList[i][cur][1];
			size = balls[index][ballsize];
			answer[index] = result;
			sum += size;
		}
	}

	for (int i = 0; i < numBalls; i++) {
		printf("%d\n", answer[i]);
	}
	return 0;
}