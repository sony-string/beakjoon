#include <bits/stdc++.h>
using namespace std;

int flows[202][202];
int caps[202][202];
const int S = 0, T = 201;
const int netsize = 202;
vector<int> nodes[202];
vector<int> path;
vector<bool> visited;
int N, M;
vector<int> A, B;


int applyFlow(int v = T, int mincap = 1e9) {
	if (v == S)
		return mincap;
	mincap = min(mincap, caps[path[v]][v] - flows[path[v]][v]);
	mincap = applyFlow(path[v], mincap);
	flows[path[v]][v] += mincap;
	flows[v][path[v]] -= mincap;
	return mincap;
}


bool searchAugmentPath() {
	path.assign(netsize, 0);
	visited.assign(netsize, false);
	queue<int> q;
	q.push(S);
	visited[S] = true;
	while (!q.empty()) {
		int v = q.front();
		if (v == T)
			return true;
		q.pop();
		for (const auto& dest : nodes[v]) {
			if (!visited[dest] && caps[v][dest] - flows[v][dest] > 0) {
				q.push(dest);
				visited[dest] = true;
				path[dest] = v;
			}
		}
	}
	return false;
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
		}
	}

	int f = flow();
	int maxflow = 0;
	while (f != 0) {
		maxflow += f;
		f = flow();
	}
	return maxflow;
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
	printf("%d", solve());
	return 0;
}