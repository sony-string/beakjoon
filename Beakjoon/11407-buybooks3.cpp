#include <bits/stdc++.h>
using namespace std;

int flows[202][202];
int caps[202][202];
int C[202][202];
int D[202][202];
const int S = 0, T = 201;
const int netsize = 202;
vector<int> nodes[202];
vector<int> path;
vector<int> dist;
int N, M;
vector<int> A, B;
queue<int> q;
vector<bool> inQ;

int mincost = 0;

int applyFlow(int v = T, int mincap = 1e9) {
	if (v == S)
		return mincap;
	mincap = min(mincap, caps[path[v]][v] - flows[path[v]][v]);
	mincap = applyFlow(path[v], mincap);
	flows[path[v]][v] += mincap;
	flows[v][path[v]] -= mincap;
	mincost += mincap * D[path[v]][v];
	return mincap;
}


bool searchAugmentPath() {
	path.assign(netsize, 0);
	dist.assign(netsize, (int)1e9);
	inQ.assign(netsize, false);
	dist[S] = 0;
	q.emplace(S);
	bool existPath = false;

	while (!q.empty()) {
		int v = q.front();
		q.pop();
		inQ[v] = false;
		if (v == T) {
			existPath = true;
			continue;
		}
		for (const auto& dest : nodes[v]) {
			if (caps[v][dest] - flows[v][dest] <= 0)
				continue;
			if (D[v][dest] + dist[v] < dist[dest]) {
				if (!inQ[dest]) {
					q.emplace(dest);
					inQ[dest] = true;
				}
				path[dest] = v;
				dist[dest] = D[v][dest] + dist[v];
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


void solve() {
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
		}
	}

	int f = flow();
	int maxflow = 0;
	while (f != 0) {
		maxflow += f;
		f = flow();
	}
	printf("%d\n%d", maxflow, mincost);
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
			scanf("%d", &caps[i][j]);
		}
	}
	for (int j = 101; j <= M + 100; j++) {
		for (int i = 1; i <= N; i++) {
			scanf("%d", &D[i][j]);
			D[j][i] = -D[i][j];
		}
	}
	solve();
	return 0;
}