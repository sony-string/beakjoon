#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;

vi adj[100001];
int nodes[200000];
int buk[500];
ii ran[100001];

void dfs() {
	int cnt = -1;
	vector<pair<int, int>> st;
	st.emplace_back(1, 0);
	while (!st.empty()) {
	travelsal:
		cnt++;
		auto [v, i] = st.back();
		st.pop_back();
		if (i == 0) ran[v].first = cnt;
		if (i == adj[v].size()) ran[v].second = cnt;
		for (; i < adj[v].size(); i++) {
			st.emplace_back(v, i + 1);
			st.emplace_back(adj[v][i], 0);
			goto travelsal;
		}
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
	dfs();
	int nsqrt = sqrt(ran[1].second);
	for (int q = 0; q < M; q++) {
		int x, i, w;
		scanf("%d", &x);
		if (x == 1) {
			scanf("%d %d", &i, &w);
			int s = ran[i].first, e = ran[i].second;
			if (s / nsqrt == e / nsqrt) {
				for (; s <= e; s++) {
					nodes[s] += w;
				}
			}
			else {
				for (int l = (s + nsqrt - 1) / nsqrt; l < (e + 1) / nsqrt; l++) buk[l] += w;
				for (int l = s; l / nsqrt < (s + nsqrt - 1) / nsqrt; l++) nodes[l] += w;
				for (int r = e; r / nsqrt >= (e + 1) / nsqrt; r--) nodes[r] += w;
			}
		}
		else {
			scanf("%d", &i);
			printf("%d\n", nodes[ran[i].first] + buk[ran[i].first / nsqrt]);
		}
	}
	return 0;
}