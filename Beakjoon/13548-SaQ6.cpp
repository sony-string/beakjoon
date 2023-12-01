#include <bits/stdc++.h>
using namespace std;

typedef long long li;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;


int cnt[100001];
int mcnt = 0;
int table[100001];

void add(int n) {
	table[cnt[n]++]--;
	table[cnt[n]]++;
	mcnt = max(mcnt, cnt[n]);
}

void sub(int n) {
	table[cnt[n]--]--;
	table[cnt[n]]++;
	if (cnt[n] + 1 == mcnt && table[cnt[n] + 1] == 0) mcnt--;
}

int main() {
	int N, M;
	int sqrtn;
	scanf("%d", &N);
	sqrtn = sqrt(N);
	vi arr;
	arr.assign(N + 1, 0);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &arr[i]);
	}
	scanf("%d", &M);
	vector<pair<ii, int>> qarr;
	qarr.assign(M, {});
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &qarr[i].first.first, &qarr[i].first.second);
		qarr[i].second = i;
	}
	vi ans;
	ans.assign(M, 0);
	auto cmp = [&](const pair<ii, int>& lhs, const pair<ii, int>& rhs) {
		auto& l = lhs.first;
		auto& r = rhs.first;
		if (l.first / sqrtn == r.first / sqrtn) {
			if (l.first / sqrtn % 2) {
				return l.second > r.second;
			}
			else {
				return l.second < r.second;
			}
		}
		else {
			return l.first < r.first;
		}
	};
	sort(qarr.begin(), qarr.end(), cmp);
	int l = qarr[0].first.first;
	int r = l;
	table[0] = 100000;
	while (r <= qarr[0].first.second) add(arr[r++]);	
	r--;
	ans[qarr[0].second] = mcnt;
	for (int q = 1; q < M; q++) {
		int ll = qarr[q].first.first;
		int rr = qarr[q].first.second;
		while (l > ll) add(arr[--l]);
		while (r < rr) add(arr[++r]);
		while (l < ll) sub(arr[l++]);
		while (r > rr) sub(arr[r--]);
		ans[qarr[q].second] = mcnt;
	}
	for (auto& i : ans) {
		printf("%d\n", i);
	}
	return 0;
}