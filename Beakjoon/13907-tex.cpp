#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int	dist[1001][1001];
bool inQ[1001][1001];
list<ii> adj[1001];
int N, M, K;
int S, D;
queue<ii> q;

void bfs() {
	q.emplace(S, 0);
	while (!q.empty()) {
		auto [v, t] = q.front();
		q.pop();
		if (t == N) continue;
		inQ[v][t] = false;
		for (auto& i : adj[v]) {
			if (dist[i.first][t + 1] == 0 || dist[i.first][t + 1] > dist[v][t] + i.second) {
				dist[i.first][t + 1] = dist[v][t] + i.second;
				if (!inQ[i.first][t + 1]) {
					inQ[i.first][t + 1] = true;
					q.emplace(i.first, t + 1);
				}
			}
		}
	}
}

int main() {
	scanf("%d %d %d", &N, &M, &K);
	scanf("%d %d", &S, &D);
	for (int i = 0; i < M; i++) {
		int s, e, w;
		scanf("%d %d %d", &s, &e, &w);
		adj[s].emplace_back(e, w);
		adj[e].emplace_back(s, w);
	}
	bfs();
	int maxt = 1e9;
	int ret = 1e9;
	for (int i = 0; i <= N; i++) {
		if (dist[D][i] == 0) continue;
		if (dist[D][i] < ret) {
			ret = dist[D][i];
			maxt = i;
		}
	}
	printf("%d\n", ret);
	for (int i = 0; i < K; i++) {
		int tex;
		ret = 1e9;
		scanf("%d", &tex);
		int newmaxt;
		for (int j = 0; j <= maxt; j++) {
			if (dist[D][j] == 0) continue;
			else {
				dist[D][j] += j * tex;
				if (ret > dist[D][j]) {
					ret = dist[D][j];
					newmaxt = j;
				}
			}
		}
		maxt = newmaxt;
		printf("%d\n", ret);
	}
	return 0;
}