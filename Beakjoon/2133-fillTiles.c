#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long solve(long long*** dp, int state[], int len) {
	if (dp[state[0]][state[1]][state[2]] != -1) {
		return dp[state[0]][state[1]][state[2]];
	}

	long long* dpptr = &dp[state[0]][state[1]][state[2]];
	int nextState[3] = { state[0], state[1], state[2] };

	if (nextState[1] > nextState[0] || nextState[1] > nextState[2]) {
		while (nextState[1] > nextState[0] && nextState[0] <= len - 2) {
			nextState[0] += 2;
		}
		while (nextState[1] > nextState[2] && nextState[2] <= len - 2) {
			nextState[2] += 2;
		}
		if (nextState[1] > nextState[0] || nextState[1] > nextState[2]) {
			*dpptr = 0;
			return 0;
		}
		if (dp[nextState[0]][nextState[1]][nextState[2]] != -1) {
			return dp[nextState[0]][nextState[1]][nextState[2]];
		}
		*dpptr = solve(dp, nextState, len);
		return *dpptr;
	}
	*dpptr = 0;

	for (int i = 0; i < 2; i++) {
		if (state[i] == state[i + 1] && state[i] < len) {
			nextState[i] += 1;
			nextState[i + 1] += 1;
			*dpptr += solve(dp, nextState, len);
			nextState[i] -= 1;
			nextState[i + 1] -= 1;
		}
	}

	if (state[1] <= len - 2) {
		nextState[1] += 2;
		*dpptr += solve(dp, nextState, len);
		nextState[1] -= 2;
	}

	return *dpptr;
}

int main() {
	int len;
	long long*** dp;
	int state[3] = { 0, 0, 0 };
	scanf("%d", &len);
	
	dp = (long long***)malloc((len + 1) * sizeof(long long**));
	for (int i = 0; i < (len + 1); i++) {
		dp[i] = (long long**)malloc((len + 1) * sizeof(long long*));
		for (int j = 0; j < (len + 1); j++) {
			dp[i][j] = (long long*)malloc((len + 1) * sizeof(long long));
			memset(dp[i][j], -1, (len + 1) * sizeof(long long));
		}
	}
	dp[len][len][len] = 1;
	solve(dp, state, len);
	printf("%lld", dp[0][0][0]);
	return 0;
}