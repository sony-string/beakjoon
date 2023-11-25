#include <bits/stdc++.h>
using namespace std;

typedef long long li;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int cnt[1000001];
li ans = 0;

void addcnt(int num) {
	ans += (li)cnt[num]++ * num * 2 + num;
}

void subcnt(int num) {
	ans += (li)cnt[num]-- * num * -2 + num;
}

int main() {
	int N, Q;
	scanf("%d %d", &N, &Q);
	vector<li> ansarr;
	vector<pair<ii, int>> qarr;
	vi arr;
	arr.assign(N + 1, 0);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &arr[i]);
	}
	ansarr.assign(Q, 0);
	qarr.assign(Q, {});
	int nrt = sqrt(N);
	for (int i = 0; i < Q; i++) {
		scanf("%d %d", &qarr[i].first.first, &qarr[i].first.second);
		qarr[i].second = i;
	}
	auto cmp = [&](pair<ii, int>& lhs, pair<ii, int>& rhs) {
		if (lhs.first.first / nrt == rhs.first.first / nrt) {
			if (lhs.first.first / nrt % 2) {
				return lhs.first.second < rhs.first.second;
			}
			else {
				return lhs.first.second > rhs.first.second;
			}
		}
		else {
			return lhs.first.first / nrt > rhs.first.first / nrt;
		}
	};
	sort(qarr.begin(), qarr.end(), cmp);
	
	int l = 0, r = 0;
	l = qarr[0].first.first;
	r = l;
	while (r <= qarr[0].first.second) {
		addcnt(arr[r++]);
	}
	r--;
	ansarr[qarr[0].second] = ans;
	
	for (int i = 1; i < Q; i++) {
		auto& q = qarr[i].first;
		int ll = q.first, rr = q.second;
		int ansidx = qarr[i].second;

		while (l > ll) addcnt(arr[--l]);
		while (r < rr) addcnt(arr[++r]);
		while (l < ll) subcnt(arr[l++]);
		while (r > rr) subcnt(arr[r--]);
		ansarr[ansidx] = ans;
	}
	for (auto& i : ansarr) {
		printf("%lld\n", i);
	}
	return 0;
}