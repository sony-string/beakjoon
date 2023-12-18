#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef long long li;

int main() {
	set<int> s;
	int N;
	li ans = 0;
	scanf("%d", &N);
	vi level;
	level.assign(N + 2, -1);
	s.emplace(0);
	s.emplace(N + 1);
	for (int i = 0; i < N; i++) {
		int n;
		scanf("%d", &n);
		auto l = s.upper_bound(n);
		auto r = l--;
		int lv = *l;
		int rv = *r;
		int m = max(level[lv], level[rv]);
		ans += m + 1;
		level[n] = m + 1;
		printf("%lld\n", ans);
		s.emplace(n);
	}
	return 0;
}