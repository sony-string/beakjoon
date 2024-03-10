#include <bits/stdc++.h>
using namespace std;

typedef long long li;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int main() {
	int N, S;
	vii pos;
	scanf("%d %d", &N, &S);
	pos.assign(N, {});
	vii sorted;
	for (int i = 1; i <= N; i++) {
		scanf("%d", &pos[i - 1].first);
		pos[i - 1].second = i;
	}
	sorted = pos;
	vi fuel;
	fuel.assign(N, 0);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &fuel[i - 1]);
	}
	queue<int> q;		
	sort(sorted.begin(), sorted.end());

	int l = 0, r = 0;
	for (int i = 0; i < N; i++) {
		if (pos[i].second == S) {
			l = r = i;
			break;
		}
	}
	q.push(l);
	while (!q.empty()) {
		int n = q.front();
		q.pop();
		int f = fuel[sorted[n].second - 1];
		int p = sorted[n].first;
		int ll = (int)(upper_bound(sorted.begin(), sorted.end(), make_pair(p - f, 0)) - sorted.begin());
		int rr = (int)(upper_bound(sorted.begin(), sorted.end(), make_pair(p + f, (int)1e9)) - sorted.begin()) - 1;
		while (ll < l) {
			q.push(--l);
		}
		while (rr > r) {
			q.push(++r);
		}		
	}
	vi ans;
	ans.reserve(r - l + 1);
	for (int i = l; i <= r; i++) {
		ans.push_back(sorted[i].second);
	}
	sort(ans.begin(), ans.end());
	for (const auto i : ans) {
		printf("%d ", i);
	}
	return 0;
}