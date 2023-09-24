#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<pair<int, int>> vii;

int N, M, cnt = 0;
vi chk;
vi paired;
vi matched;
vi L, R;
vector<vector<int>> nodes;

bool match(int v) {
	for (auto i : nodes[v]) {
		if (chk[i]) continue;
		chk[i] = 1;
		if (paired[i] == -1 || match(paired[i])) return (paired[i] = v);
	}
	return false;
}

void dfs(int v) {
	L[v] = 1;
	cnt++;
	for (auto i : nodes[v]) {
		if (chk[i]) continue;
		chk[i] = 1;
		R.push_back(i);
		dfs(paired[i]);
	}
}

int solve() {
	int f = 0;
	paired.assign(M + 1, -1);
	matched.assign(N + 1, 0);
	for (int i = 1; i <= N; i++) {
		chk.assign(M + 1, 0);
		if (match(i)) {
			f++; matched[i] = 1;
		}
	}
	L.assign(N + 1, 0);
	chk.assign(M + 1, 0);
	for (int i = 1; i <= N; i++) {
		if (matched[i])
			continue;
		dfs(i);
	}
	sort(R.begin(), R.end());
	cnt = N - cnt;
	return f;
}

int main() {
	int d;
	scanf("%d %d", &N, &M);
	nodes.assign(N + 1, {});
	for (int i = 1; i <= N; i++) {
		scanf("%d", &d);
		nodes[i].assign(d, 0);
		for (int j = 0; j < d; j++) {
			scanf("%d", &nodes[i][j]);
		}
	}
	printf("%d\n", solve());
	printf("%d", cnt);
	for (int i = 1; i <= N; i++) {
		if (!L[i])
			printf(" %d", i);
	}
	printf("\n%d", R.size());
	for (auto& i : R) {
		printf(" %d", i);
	}

	return 0;
}