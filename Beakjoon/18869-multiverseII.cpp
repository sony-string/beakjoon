#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

int comp(int n, int m) {
	if (n > m) return 1;
	else if (n == m) return 0;
	else return -1;
}

int main() {
	int M, N;
	scanf("%d %d", &M, &N);
	vector<vii> arr(M);
	for (int i = 0; i < M; i++) {
		arr[i].assign(N, { 0, 0 });
		for (int j = 0; j < N; j++) {
			scanf("%d", &arr[i][j].first);
			arr[i][j].second = j;
		}
		sort(arr[i].begin(), arr[i].end());
	}
	int cnt;
	long long ans = 0;
	vector<bool> chk(M, false);
	for (int i = 0; i < M; i++) {
		if (chk[i]) continue;
		cnt = 1;
		chk[i] = 1;
		for (int j = i + 1; j < M; j++) {
			if (chk[j]) continue;
			bool ok = true;
			for (int k = 0; k < N - 1 && ok; k++) {
				if (arr[i][k].second != arr[j][k].second) ok = false;
				else {
					if (comp(arr[i][k + 1].first, arr[i][k].first) != comp(arr[j][k + 1].first, arr[j][k].first))
						ok = false;
				}
			}
			if (ok) { chk[j] = true; cnt++; }
		}
		ans += cnt * (cnt - 1) / 2;
	}
	printf("%lld", ans);
	return 0;
}