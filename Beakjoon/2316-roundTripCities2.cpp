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

	bool getAugPath(int start, int dest) {
		queue<int> q({ start });
		visited.assign(size, false);
		int v;
		bool isExist = false;

		while (!q.empty()) {
			v = q.front(); q.pop();
			if (v == dest) {
				isExist = true;
				break;
			}
			for (auto& edge : network[v].edges) {
				if (capMat[v][edge] - flowMat[v][edge] > 0 && !visited[edge]) {
					visited[edge] = true;
					q.push(edge);
					augPath[edge] = v;
				}
			}
		}
		return isExist;
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
	int N, P;
	int s, e;
	int maxflow = 0;
	int flow = 0;
	scanf("%d %d", &N, &P);
	Network net(2 * (N + 1));
	net.addEdge(1, N + 1, N);
	net.addEdge(2, N + 2, N);
	for (int i = 3; i <= N; i++) {
		net.addEdge(i, N + i);
	}
	for (int i = 0; i < P; i++) {
		scanf("%d %d", &s, &e);
		net.addEdge(s + N, e);
		net.addEdge(e + N, s);
	}

	flow = net.flow(1, 2);
	while (flow != 0) {
		maxflow += flow;
		flow = net.flow(1, 2);
	}

	printf("%d", maxflow);
	return 0;
}