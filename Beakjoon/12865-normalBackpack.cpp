#include <bits/stdc++.h>
using namespace std;


int solve(int N, int K, const vector<pair<int, int>>& stuff) {
	int** dp = new int* [N + 1];
	for (int i = 0; i < N + 1; i++) {
		dp[i] = new int[K + 1];
		memset(dp[i], -1, sizeof(int) * (K + 1));
	}
	dp[0][0] = 0;
	for (int i = 0; i < N; i++) {
		for (int k = 0; k <= K; k++) {
			if (dp[i][k] < 0)
				continue;
			if (k + stuff[i].first <= K && dp[i + 1][k + stuff[i].first] < dp[i][k] + stuff[i].second)
				dp[i + 1][k + stuff[i].first] = dp[i][k] + stuff[i].second;
			if (dp[i + 1][k] < dp[i][k])
				dp[i + 1][k] = dp[i][k];
		}
	}
	int ans = -1;
	for (int k = 0; k <= K; k++)
		ans = max(ans, dp[N][k]);
	return ans;
}

int main() {
	int N, K;
	vector<pair<int, int>> stuff;

	scanf("%d %d", &N, &K);
	stuff.assign(N, { 0,0 });
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &stuff[i].first, &stuff[i].second);
	}

	printf("%d", solve(N, K, stuff));
}