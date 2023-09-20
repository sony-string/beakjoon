#include <bits/stdc++.h>
using namespace std;

int flows[202][202];
int caps[202][202];
int C[202][202];
const int S = 0, T = 201;
const int netsize = 202;
vector<int> nodes[202];
vector<int> path;
vector<int> dist;
int N, M;
vector<int> A, B;
priority_queue<pair<int, int>> q;

int mincost = 0;

int applyFlow(int v = T, int mincap = 1e9) {
	if (v == S)
		return mincap;
	mincap = min(mincap, caps[path[v]][v] - flows[path[v]][v]);
	mincap = applyFlow(path[v], mincap);
	flows[path[v]][v] += mincap;
	flows[v][path[v]] -= mincap;
	mincost += mincap * C[path[v]][v];
	return mincap;
}


bool searchAugmentPath() {
	path.assign(netsize, 0);
	dist.assign(netsize, (int)1e9);
	dist[S] = 0;
	q.emplace(0, S);
	bool existPath = false;

	while (!q.empty()) {
		int v = q.top().second;
		int d = q.top().first;
		q.pop();
		if (v == T) {
			existPath = true;
			continue;
		}
		if (d > dist[v])
			continue;
		for (const auto& dest : nodes[v]) {
			if (caps[v][dest] - flows[v][dest] <= 0)
				continue;
			if (C[v][dest] + d < dist[dest]) {
				q.emplace(C[v][dest] + d, dest);
				path[dest] = v;
				dist[dest] = C[v][dest] + d;
			}
		}
	}
	return existPath;
}


int flow() {
	if (searchAugmentPath())
		return applyFlow();
	else
		return 0;
}


int solve() {
	for (int i = 1; i <= N; i++) {
		nodes[S].push_back(i);
		nodes[i].push_back(S);
		caps[S][i] = A[i];
	}
	for (int i = 101; i <= M + 100; i++) {
		nodes[i].push_back(T);
		nodes[T].push_back(i);
		caps[i][T] = B[i - 100];
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 101; j <= M + 100; j++) {
			nodes[i].push_back(j);
			nodes[j].push_back(i);
			caps[i][j] = A[i];
		}
	}

	int f = flow();
	while (f != 0) {
		f = flow();
	}
	return mincost;
}

int main() {
	scanf("%d %d", &N, &M);
	A.assign(N + 1, 0);
	B.assign(M + 1, 0);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &A[i]);
	}
	for (int i = 1; i <= M; i++) {
		scanf("%d", &B[i]);
	}
	for (int j = 101; j <= M + 100; j++) {
		for (int i = 1; i <= N; i++) {
			scanf("%d", &C[i][j]);
			C[j][i] = -C[i][j];
		}
	}
	printf("%d", solve());
	return 0;
}