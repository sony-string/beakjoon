#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int dp[2][3000];
int cnt = 0;
vector<vi> adj;
vii net;
vi candy;
int N, M, K;
int befo, now;
bool visited[30001];

void bfs(int V) {
	int size = 0;
	int sumcandy = 0;
	visited[V] = true;
	queue<int> q({ V });
	while (!q.empty()) {
		int v = q.front();
		sumcandy += candy[v];
		size++;
		q.pop();
		for (auto& i : adj[v]) {
			if (visited[i]) continue;
			visited[i] = true;
			q.emplace(i);
		}
	}
	net.emplace_back(size, sumcandy);
	cnt++;
}

int solve() {
	fill(dp[1], dp[1] + 3000, -1);
	int ret = 0;
	befo = 1;
	now = 0;
	dp[1][0] = 0;
	for (int i = 0; i < cnt; i++) {
		fill(dp[now], dp[now] + 3000, -1);
		dp[now][0] = 0;
		if (net[i].first < K) dp[now][net[i].first] = net[i].second;
		for (int j = 0; j < K; j++) {
			if (dp[befo][j] == -1) continue;
			dp[now][j] = max(dp[now][j], dp[befo][j]);
			if (j + net[i].first >= K) continue;
			else {
				dp[now][j + net[i].first] = max(dp[now][j + net[i].first], dp[befo][j] + net[i].second);
			}
		}
		swap(befo, now);
	}
	for (int i = 0; i <= K; i++) {
		ret = max(ret, dp[befo][i]);
	}
	return ret;
}

int main() {
	scanf("%d %d %d", &N, &M, &K);
	candy.assign(N + 1, 0);
	adj.assign(N + 1, {});
	for (int i = 1; i <= N; i++) {
		scanf("%d", &candy[i]);
	}
	for (int i = 0; i < M; i++) {
		int s, e;
		scanf("%d %d", &s, &e);
		adj[s].push_back(e);
		adj[e].push_back(s);
	}
	for (int i = 1; i <= N; i++) {
		if (visited[i]) continue;
		bfs(i);
	}
	printf("%d", solve());
	return 0;
}