#include <bits/stdc++.h>
using namespace std;


typedef long long li;
typedef vector<int> vi;


li inv_cnt(vi& arr, int l, int r, int e) {
	li ret = 0;
	if (e - l == 1) return 0;
	else {
		ret += inv_cnt(arr, l, (l + r + 1) / 2, r);
		ret += inv_cnt(arr, r, (r + e + 1) / 2, e);
	}
	int ll = l, rr = r, i = 0;
	vi sub(e - l, 0);

	while (ll < r && rr < e) {		
		if (arr[ll] <= arr[rr]) {
			sub[i++] = arr[ll++];
		}
		else {
			ret += r - ll;
			sub[i++] = arr[rr++];
		}
	}
	while (ll < r) sub[i++] = arr[ll++];
	while (rr < e) sub[i++] = arr[rr++];

	for (auto n : sub) {
		arr[l++] = n;
	}
	return ret;
}


int main() {
	int T;

	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int N, M, K;
		scanf("%d %d %d", &N, &M, &K);
		vector<array<int, 2>> roads(K);
		for (auto& r : roads) {
			scanf("%d %d", &r[0], &r[1]);
		}
		sort(roads.begin(), roads.end());

		vi dests;
		dests.reserve(K + 1);
		for (int i = 0; i < K; i++) {
			if (i == K - 1 || roads[i] != roads[i + 1]) {
				dests.push_back(roads[i][1]);
			}
		}
		printf("Test case %d: %lld\n", t, 
			inv_cnt(dests, 0, (K + 1) / 2, K));
	}
	return 0;
}