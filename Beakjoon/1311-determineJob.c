#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

int fullMask = 0, bit = 1;
int bits[20];

int dfs(int** dp, int** costArr, int visited, int depth, int size) {
	if (visited == fullMask) {
		return 0;
	}
	if (dp[depth][visited] != -1) {
		return dp[depth][visited];
	}
	int sum;
	for (int i = 0; i < size; i++) {
		if ((bits[i] & visited) == bits[i]) {
			continue;
		}
		sum = dfs(dp, costArr, visited | bits[i], depth + 1, size) + costArr[depth][i];
		if (dp[depth][visited] == -1) {
			dp[depth][visited] = sum;
		}
		else if (dp[depth][visited] > sum) {
			dp[depth][visited] = sum;
		}
	}
	return dp[depth][visited];
}

int main() {
	int numJobs;
	int** costArr;
	int** dp;
	int count = 0;
	scanf("%d", &numJobs);
	costArr = (int**)malloc(numJobs * sizeof(int*));
	dp = (int**)calloc(numJobs, sizeof(int*));
	for (int i = 0; i < numJobs; i++) {
		costArr[i] = (int*)malloc(numJobs * sizeof(int));
		fullMask += bit;
		bits[i] = bit;
		bit <<= 1;
		for (int j = 0; j < numJobs; j++) {
			scanf("%d", &costArr[i][j]);
		}
	}
	for (int i = 0; i < numJobs; i++) {
		dp[i] = (int*)malloc((fullMask + 1) * sizeof(int));
		memset(dp[i], -1, (fullMask + 1) * sizeof(int));
	}
	dfs(dp, costArr, 0, 0, numJobs);
	printf("%d", dp[0][0]);
	return 0;
}