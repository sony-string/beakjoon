#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

int fullMask = 0;
int bits[16];


int solve(int*** dp, int** costArr, int visited, int size, int src, int cur) {
	if (visited == fullMask) {
		if (costArr[cur][src] == 0) {
			dp[src][cur][fullMask] = INT_MAX;
		}
		else {
			dp[src][cur][fullMask] = costArr[cur][src];
		}
		return dp[src][cur][fullMask];
	}
	if (dp[src][cur][visited] != 0) {
		return dp[src][cur][visited];
	}
	dp[src][cur][visited] = INT_MAX;
	int result;
	for (int i = 0; i < size; i++) {
		if ((visited & bits[i]) == bits[i] || costArr[cur][i] == 0) {
			continue;
		}
		result = solve(dp, costArr, visited | bits[i], size, src, i);
		if (result == INT_MAX) {
			continue;
		}
		else if (dp[src][cur][visited] > result + costArr[cur][i]) {
			dp[src][cur][visited] = result + costArr[cur][i];
		}
	}
	return dp[src][cur][visited];
}

int main() {
	int*** dp;
	int numCities, bit = 1;
	int** costArr;
	scanf("%d", &numCities);
	fullMask = (1 << numCities) - 1;

	costArr = (int**)malloc(numCities * sizeof(int*));
	dp = (int***)malloc(numCities * sizeof(int**));
	for (int i = 0; i < numCities; i++) {
		bits[i] = bit;
		bit <<= 1;
		costArr[i] = (int*)malloc(numCities * sizeof(int));
		dp[i] = (int**)malloc(numCities * sizeof(int*));
		for (int j = 0; j < numCities; j++) {
			dp[i][j] = (int*)calloc((fullMask + 1), sizeof(int));
			scanf("%d", &costArr[i][j]);
		}
	}

	for (int i = 0; i < numCities; i++) {
		solve(dp, costArr, bits[i], numCities, i, i);
	}
	int result = INT_MAX;
	for (int i = 0; i < numCities; i++) {
		if (dp[i][i][bits[i]] < result) {
			result = dp[i][i][bits[i]];
		}
	}
	printf("%d", result);
	return 0;
}