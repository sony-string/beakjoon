#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef pair<ii, int> item;
typedef vector<item> vii;

int cnt[1'000'000];
int main() {
	int N, Q;
	int sqrtn;
	auto cmp = [&](const item& lhs, const item& rhs) {
		if (lhs.first.first / sqrtn == rhs.first.first / sqrtn) {
			if ((lhs.first.first / sqrtn) % 2 == 1) {
				return lhs.first.second > rhs.first.second;
			}
			else {
				return lhs.first.second < rhs.first.second;
			}
		}
		else {
			return lhs.first.first / sqrtn < rhs.first.first / sqrtn;
		}
	};

	vii queries;
	vi arr, ansarr;
	scanf("%d", &N);
	sqrtn = sqrt(N);
	arr.assign(N, 0);
	map<int, int> numset;
	int idxcnt = 0;
	for (auto& i : arr) {
		scanf("%d", &i);
		auto it = numset.find(i);
		if (it == numset.end()) {
			numset.emplace(i, idxcnt++);
			i = idxcnt - 1;
		}
		else {
			i = (*it).second;
		}
	}
	scanf("%d", &Q);
	queries.assign(Q, {});
	ansarr.assign(Q, 0);
	for (int i = 0; i < Q; i++) {
		scanf("%d %d", &queries[i].first.first, &queries[i].first.second);
		queries[i].first.first--;
		queries[i].first.second--;
		queries[i].second = i;
	}
	sort(queries.begin(), queries.end(), cmp);
	int l = -1, r = -1;
	l = r = queries[0].first.first;
	int ans = 0;
	while (r <= queries[0].first.second) cnt[arr[r++]]++ ? 0 : ans++;
	r--;
	ansarr[queries[0].second] = ans;
	for (int i = 1; i < Q; i++) {
		int ll = queries[i].first.first;
		int rr = queries[i].first.second;
		int idx = queries[i].second;

		while (ll < l) cnt[arr[--l]]++ ? 0 : ans++;
		while (rr > r) cnt[arr[++r]]++ ? 0 : ans++;
		while (ll > l) --cnt[arr[l++]] ? 0 : ans--;
		while (rr < r) --cnt[arr[r--]] ? 0 : ans--;
		ansarr[idx] = ans;
	}
	for (auto& i : ansarr) {
		printf("%d\n", i);
	}
	return 0;
}