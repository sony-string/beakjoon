#include <bits/stdc++.h>
using namespace std;

typedef struct Edge {
	int first, second;
	int c, f;
	Edge* dual;
	Edge() : dual(0) {}
	Edge(int first, int second, int cap, int flow) : first(first), second(second), c(cap), f(flow) {};
} Edge;

int S = 0, T = 801;
int N, M;
int total = 0;
list<Edge> nodes[802];
queue<int> q;
vector<bool> inq;
vector<Edge*> path;
vector<int> dist;

void augment(int v = T, int mincap = 1e9) {
	if (v == S) return;
	mincap = min(mincap, path[v]->c - path[v]->f);
	augment(path[v]->dual->first, mincap);
	total += mincap * path[v]->second;
	path[v]->f += mincap;
	path[v]->dual->f -= mincap;
}

bool spfa() {
	q.push(S);
	inq.assign(802, false);
	path.assign(802, 0);
	dist.assign(802, 1e9);
	dist[S] = 0;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		if (v == T) continue;
		inq[v] = false;
		for (auto& e : nodes[v]) {
			if (e.c - e.f > 0 && dist[v] + e.second < dist[e.first]) {
				dist[e.first] = dist[v] + e.second;
				path[e.first] = &e;
				if (!inq[e.first]) {
					inq[e.first] = true;
					q.push(e.first);
				}
			}
		}
	}
	return path[T] != 0;
}

int solve() {
	int f = 0;
	while (spfa()) {
		f++;
		augment();
	}
	return f;
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		nodes[0].emplace_back(i, 0, 1, 0);
		nodes[i].emplace_back(0, 0, 0, 0);
		nodes[0].back().dual = &nodes[i].back();
		nodes[i].back().dual = &nodes[0].back();
		int n, e, c;
		scanf("%d", &n);
		for (int j = 0; j < n; j++) {
			scanf("%d %d", &e, &c);
			e += 400;
			nodes[i].emplace_back(e, c, 1, 0);
			nodes[e].emplace_back(i, -c, 0, 0);
			nodes[i].back().dual = &nodes[e].back();
			nodes[e].back().dual = &nodes[i].back();
		}
	}

	for (int i = 401; i <= M + 400; i++) {
		nodes[i].emplace_back(T, 0, 1, 0);
		nodes[T].emplace_back(i, 0, 0, 0);
		nodes[i].back().dual = &nodes[T].back();
		nodes[T].back().dual = &nodes[i].back();
	}
	printf("%d\n", solve());
	printf("%d", total);
	return 0;
}