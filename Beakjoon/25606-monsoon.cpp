#include <bits/stdc++.h>
using namespace std;

int main() {
	int N, M, Q, n;
	int cnt = 0;
	int until;
	vector<int> sum;
	vector<int> sub;
	vector<int> left;
	vector<int> subcor;
	scanf("%d %d %d", &N, &M, &Q);
	sum.assign(N + 1, 0);
	sub.assign(N + 1, 0);
	left.assign(N + 1, 0);
	subcor.assign(N + 1, 0);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &n);
		until = 1 + i + n / M;
		if (until <= N) {
			left[until] ++;
			subcor[until] += n % M;
		}
		sum[i] = sum[i - 1] + n;
		cnt -= left[i];
		sub[i] = cnt * M + sub[i - 1];
		sub[i] += subcor[i];
		cnt++;
	}

	for (int q = 0; q < Q; q++) {
		int t;
		scanf("%d %d", &n, &t);
		if (n == 1) {
			printf("%d\n", sum[t] - sub[t]);
		}
		else {
			printf("%d\n", sub[t] - sub[t - 1]);
		}
	}
	return 0;
}