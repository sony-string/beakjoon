#include <bits/stdc++.h>
using namespace std;

int d[101][101];

void floyd(int N) {
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (d[i][k] == -1 || d[k][j] == -1) continue;
				if (d[i][j] == -1 || d[i][k] + d[k][j] < d[i][j]) {
					d[i][j] = d[i][k] + d[k][j];
				}
			}
		}
	}
}

int main() {
	int T;
	int N, M, K;
	vector<int> f;
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		memset(d, -1, sizeof(d));
		scanf("%d %d", &N, &M);
		for (int i = 1; i <= N; i++) {
			d[i][i] = 0;
		}
		int s, e, c;
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &s, &e, &c);
			d[s][e] = c;
			d[e][s] = c;
		}
		floyd(N);
		scanf("%d", &K);
		f.assign(K, 0);
		for (int i = 0; i < K; i++) {
			scanf("%d", &f[i]);
		}
		long long ans_ = 1e13;
		int ans;
		for (int i = 1; i <= N; i++) {
			long long sum = 0;
			for (int k = 0; k < K; k++) {
				sum += d[f[k]][i];
			}
			if (sum < ans_) {
				ans_ = sum;
				ans = i;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}