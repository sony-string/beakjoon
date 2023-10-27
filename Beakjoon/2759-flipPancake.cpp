#include <bits/stdc++.h>
using namespace std;

int main() {
	int T;
	vector<int> arr;
	vector<int> ans;
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		int N;
		scanf("%d", &N);
		arr.assign(N + 1, 0);
		arr[0] = -1;
		ans.assign(2 * N - 2, 0);
		for (auto& i : arr) {
			if (i == -1) continue;
			scanf("%d", &i);
		}
		int k, b = N;
		int cnt = 0;
		for (b = N; b > 2; b--) {
			k = 1;
			for (int i = 1; i <= b; i++) {
				k = arr[i] > arr[k] ? i : k;
			}
			if (k == 0) {
				ans[cnt++] = b;
				reverse(arr.begin() + 1, arr.begin() + b + 1);
			}
			else if (k != N) {
				ans[cnt++] = k;
				reverse(arr.begin() + 1, arr.begin() + k + 1);
				ans[cnt++] = b;
				reverse(arr.begin() + 1, arr.begin() + b + 1);
			}
		}
		if (arr[1] == 2) ans[cnt++] = 2;
		printf("%d", cnt);
		for (int i = 0; i < cnt; i++) {
			printf(" %d", ans[i]);
		}
		printf("\n");
	}
	return 0;
}