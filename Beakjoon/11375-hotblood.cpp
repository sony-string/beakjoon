#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

const int S = 0;
const int T = 2001;


typedef struct Node {
	vi edges;
	void addEdge(int dest) {
		edges.emplace_back(dest);
	}
} Node;

typedef struct Network {
	int size;
	int** flowMat, ** capMat;
	vector<Node> network;
	vector<bool> visited;
	vi augPath;

	Network(int n) {
		size = n;
		network.assign(n, Node());
		visited.assign(n, false);
		flowMat = new int* [n];
		capMat = new int* [n];
		for (int i = 0; i < n; i++) {
			flowMat[i] = new int[n];
			memset(flowMat[i], 0, sizeof(int) * n);
			capMat[i] = new int[n];
			memset(capMat[i], 0, sizeof(int) * n);
		}
	}

	void addEdge(int start, int dest, int cap = 1) {
		network[start].addEdge(dest);
		network[dest].addEdge(start);
		capMat[start][dest] = cap;
		capMat[dest][start] = 0;
	}

	bool dfs(int v, const int& dest) {
		visited[v] = true;
		if (v == dest) {
			return true;
		}
		for (auto edge : network[v].edges) {
			if (capMat[v][edge] - flowMat[v][edge] > 0 && !visited[edge]) {
				augPath[edge] = v;
				if (dfs(edge, dest)) {
					return true;
				}
			}
		}
		return false;
	}

	bool getAugPath(int start, int dest) {
		visited.assign(size, false);
		return dfs(start, dest);
	}

	void augment(int v, int& minEdge, const int& start) {
		if (v == start) {
			return;
		}
		else {
			minEdge = minEdge < capMat[augPath[v]][v] - flowMat[augPath[v]][v] ?
				minEdge : capMat[augPath[v]][v] - flowMat[augPath[v]][v];
			augment(augPath[v], minEdge, start);
			flowMat[augPath[v]][v] += minEdge;
			flowMat[v][augPath[v]] -= minEdge;
		}
	}

	int flow(int start, int dest) {
		int f = 1e9;
		augPath.assign(size, -1);
		if (!getAugPath(start, dest)) {
			return 0;
		}

		augment(dest, f, start);
		return f;
	}
} Network;

int main() {
	int N, M;
	int job;
	int jobCount;
	int maxflow = 0;
	int flow;
	Network net(T + 1);
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		net.addEdge(S, i);
	}
	for (int i = 1001; i <= M + 1000; i++) {
		net.addEdge(i, T);
	}

	for (int i = 1; i <= N; i++) {
		scanf("%d", &jobCount);
		for (int j = 0; j < jobCount; j++) {
			scanf("%d", &job);
			net.addEdge(i, job + 1000);
		}
	}

	flow = net.flow(S, T);
	while (flow > 0) {
		maxflow += flow;
		flow = net.flow(S, T);
	}

	printf("%d", maxflow);
	return 0;
}