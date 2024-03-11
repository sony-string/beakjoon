#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

constexpr int SIZE = 550;
constexpr int S = 0; 
constexpr int T = 510;
typedef struct Network {
private:
	int costs[SIZE][SIZE];
	int caps[SIZE][SIZE];
	int flows[SIZE][SIZE];
	int totalflow = 0, totalcost = 0;
	int path[SIZE];
	int dists[SIZE];

	bool findpath() {
		fill(path, path + SIZE, -1);
		fill(dists, dists + SIZE, (int)1e9);
		dists[0] = 0;
		queue<int> q;
		bool chk[SIZE];
		fill(chk, chk + SIZE, false);
		q.emplace(S);
		chk[S] = true;

		while (!q.empty()) {
			int s = q.front();
			q.pop();
			if (s == T) continue;
			chk[s] = false;
			for (int e = 0; e <= T; e++) {
				if (caps[s][e] - flows[s][e] <= 0) continue;
				if (dists[e] > dists[s] + costs[s][e]) {
					if (!chk[e])
						q.push(e);
					chk[e] = true;
					dists[e] = dists[s] + costs[s][e];
					path[e] = s;
				}
			}
		}

		return path[T] != -1;
	}
	void apply(int v = T) {
		if (v == S) return;
		assert(v != -1);
		flows[path[v]][v] += 1;
		flows[v][path[v]] -= 1;
		totalcost += costs[path[v]][v];
		apply(path[v]);
	}
public:
	Network() {
		memset(costs, 0, sizeof(int) * SIZE * SIZE);
		memset(caps, 0, sizeof(int) * SIZE * SIZE);
		memset(flows, 0, sizeof(int) * SIZE * SIZE);
		fill(path, path + SIZE, -1);
		fill(dists, dists + SIZE, (int)1e9);
	}
	void addEdge(int s, int e, int c, int cap = 1) {
		costs[s][e] = c;
		caps[s][e] = cap;
		costs[e][s] = -c;		
	}

	void run(int N, int maxstories[]) {
		for (int i = N + 1; i < N + 4; i++) {
			caps[i][T] = 1;
		}		

		while (findpath()) {			
			apply();
			totalflow++;			
		}
		for (int i = N + 1; i < N + 4; i++) {
			caps[i][T] = maxstories[i - N - 1];
		}
		while (findpath()) {
			if (dists[T] >= 0 && flows[path[T]][T] > 0) {
				caps[path[T]][T] = 1;
				continue;
			}
			apply();
			totalflow++;
		}
	}
	int gettotalcost() {
		return totalcost;
	}
	
} Network;

Network net;
int main() {
	int N;
	int A, B, C;
	scanf("%d %d %d %d", &N, &A, &B, &C);
	int maxstories[3] = { A, B, C };
	for (int i = 1; i <= N; i++) {
		net.addEdge(S, i, 0, 1);
	}
	for (int i = N + 1; i < N + 4; i++) {
		net.addEdge(i, T, 0, maxstories[i - N - 1]);
	}
	for (int i = 1; i <= N; i++) {
		for (int k = 1; k <= 3; k++) {
			int c;
			scanf("%d", &c);
			net.addEdge(i, N + k, -c);
		}
	}
	net.run(N, maxstories);
	printf("%d", -1 * net.gettotalcost());
	return 0;
}