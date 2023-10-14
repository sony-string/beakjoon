#include <bits/stdc++.h>
using namespace std;

int ans;
int V, E;
int S = 1, T;
int dist[2001][2001];
int f[2001][2001];
int c[2001][2001];
const int off = 1000;

typedef struct Network {
	int size;
	vector<list<int>> network;
	vector<int> path;
	void addEdge(int s, int d, int cost) {
		network[s + off].push_back(d);
		network[d].push_back(s + off);
		c[s + off][d] = 1;
		dist[s + off][d] = cost;
		dist[d][s + off] = -cost;
	}
	void makenet(int v) {
		memset(dist, 0, sizeof(int[2001][2001]));
		memset(f, 0, sizeof(int[2001][2001]));
		memset(c, 0, sizeof(int[2001][2001]));
		T = v;
		size = 2001;
		network.assign(size, {});
		for (int i = 0; i <= 1000; i++) {
			network[i].push_back(i + off);
			network[i + off].push_back(i);
			c[i][i + off] = 1;
		}
		c[S][S + off] = 2;
		ans = 0;
		path.assign(size, 0);
	}
	void augment(int v = T) {
		if (v == S) return;
		int s = path[v];
		ans += dist[s][v];
		f[s][v] += 1;
		f[v][s] -= 1;
		augment(s);
	}
	void spfa() {
		int v;
		queue<int> q;
		vector<bool> inQ;
		vector<int> dists;
		inQ.assign(size, false);
		dists.assign(size, 1e9);
		inQ[S] = true;
		dists[S] = 0;
		q.push(S);
		while (!q.empty()) {
			v = q.front();
			q.pop();
			if (v == T) continue;
			inQ[v] = false;
			for (const auto& d : network[v]) {
				if (c[v][d] - f[v][d] <= 0) continue;
				if (dists[d] > dists[v] + dist[v][d]) {
					if (!inQ[d]) {
						inQ[d] = true;
						q.push(d);
					}
					dists[d] = dists[v] + dist[v][d];
					path[d] = v;
				}
			}
		}
	}
	void solve() {
		spfa();
		augment();
		spfa();
		augment();
		printf("%d\n", ans);
	}
} Network;

int main() {
	while (scanf("%d %d", &V, &E) != EOF) {
		T = V;
		Network net;
		net.makenet(V);
		for (int i = 0; i < E; i++) {
			int s, d, cost;
			scanf("%d %d %d", &s, &d, &cost);
			net.addEdge(s, d, cost);
		}
		net.solve();
	}
	return 0;
}