#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

vi adj[100001];
int ans[100001];
vi sum;

void dfs() {
	vector<tuple<int, int, int>> st;
	st.emplace_back(0, 1, 0);
	while (!st.empty()) {
	travelsal:
		auto [w, v, i] = st.back();
		st.pop_back();
		for (; i < adj[v].size(); i++) {
			st.emplace_back(w, v, i + 1);
			st.emplace_back(w + sum[v], adj[v][i], 0);
			goto travelsal;
		}
		ans[v] = w + sum[v];
	}
}

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		int n;
		scanf("%d", &n);
		if (n == -1) continue;
		adj[n].push_back(i);
	}
	sum.assign(N + 1, 0);
	for (int i = 0; i < M; i++) {
		int n, w;
		scanf("%d %d", &n, &w);
		sum[n] += w;
	}
	dfs();
	for (int i = 1; i <= N; i++) {
		printf("%d ", ans[i]);
	}
	return 0;
}