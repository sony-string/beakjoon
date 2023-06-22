#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;

int* wineAmountArr;
int** dp;
int numGlasses;

int solve() {
	for (int i = 0; i < numGlasses; i++) {
		for (int k = 0; k < 3; k++) {
			if (dp[i][k] != -1) {
				if (k == 2) {
					dp[i + 1][0] = max(dp[i + 1][0], dp[i][k]);
					continue;
				}
				dp[i + 1][k + 1] = max(dp[i + 1][k + 1], dp[i][k] + wineAmountArr[i]);
				dp[i + 1][0] = max(dp[i + 1][0], dp[i][k]);
			}
		}
	}
	
	int result = -1;
	for (int k = 0; k < 3; k++) {
		result = max(result, dp[numGlasses][k]);
	}
	return result;
}

int main() {
	dp = new int* [10001];
	wineAmountArr = new int[10001];
	for (int i = 0; i < 10001; i++) {
		dp[i] = new int[3];
		memset(dp[i], -1, sizeof(int) * 3);
	}
	
	scanf("%d", &numGlasses);
	for (int i = 0; i < numGlasses; i++) {
		scanf("%d", &wineAmountArr[i]);
	}
	dp[0][0] = 0;
	printf("%d", solve());
	return 0;
}