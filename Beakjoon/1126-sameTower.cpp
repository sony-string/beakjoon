#include <bits/stdc++.h>
using namespace std;

int memo[2][500'001];
int* dp[2] = { memo[0], memo[1] };

void update(int H) {
	for (int i = 0; i <= 500'000; i++) {
		if (dp[0][i] != -1) {
			dp[1][i] = max(dp[0][i], dp[1][i]);
			int h = H + i;
			if (h <= 500'000)
				dp[1][h] = max(dp[1][h], dp[0][i]);
			h = i - H;
			if (h <= 500'000) {
				if (h >= 0)
					dp[1][h] = max(dp[1][h], dp[0][i] + H);
				else
					dp[1][-h] = max(dp[1][-h], dp[0][i] + i);
			}
		}
	}
	swap(dp[0], dp[1]);
}

int solve(int N, const vector<int>& arr) {
	memset(memo, -1, sizeof(int[2][500'001]));
	memo[0][0] = 0; memo[1][0] = 0;
	for (const auto& i : arr) {
		update(i);
	}
	if (dp[0][0] == 0)
		return -1;
	else
		return dp[0][0];
}

int main() {
	int N;
	vector<int> arr;
	scanf("%d", &N);
	arr.assign(N, 0);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
	printf("%d", solve(N ,arr));
	return 0;
}