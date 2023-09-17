#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;


int S, T;
int N, M;

inline int getIndex(int i, int j) {
	return i * (M + 2) + j;
}

typedef struct Edge {
	int dest;
	int flow;
	int cap;
	Edge* dual;
	Edge(int d, int f, int c) : dest(d), flow(f), cap(c) {}
} Edge;

typedef struct Node {
	list<Edge> edges;
	void addEdge(int dest, int flow, int cap) {
		edges.emplace_back(dest, flow, cap);
	}
} Node;

typedef struct Network {
	int size;
	vector<Node> network;
	vector<bool> visited;
	vector<Edge*> augPath;

	Network(int n) {
		size = n;
		network.assign(n, Node());
		visited.assign(n, false);
	}

	void addEdge(int start, int dest, int cap = 1) {
		network[start].addEdge(dest, 0, cap);
		network[dest].addEdge(start, 0, 0);
		network[start].edges.back().dual = &network[dest].edges.back();
		network[dest].edges.back().dual = &network[start].edges.back();
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
				if (edge.cap - edge.flow > 0 && !visited[edge.dest]) {
					visited[edge.dest] = true;
					q.push(edge.dest);
					augPath[edge.dest] = &edge;
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
			minEdge = minEdge < augPath[v]->cap - augPath[v]->flow ?
				minEdge : augPath[v]->cap - augPath[v]->flow;
			augment(augPath[v]->dual->dest, minEdge, start);
			augPath[v]->flow += minEdge;
			augPath[v]->dual->flow -= minEdge;
		}
	}

	int flow(int start, int dest) {
		int f = 1e9;
		augPath.assign(size, 0);
		if (!getAugPath(start, dest)) {
			return 0;
		}

		augment(dest, f, start);
		return f;
	}
} Network;

int main() {
	char** map;
	int mapSize;
	
	scanf("%d %d", &N, &M);
	map = new char* [N + 2];
	for (int i = 1; i < N + 1; i++) {
		map[i] = new char[M + 3];
		scanf("%s", map[i] + 1);
		map[i][0] = '#';
		map[i][M + 1] = '#';
		map[i][M + 2] = 0;
	}
	map[0] = new char[M + 3];
	memset(map[0], '#', M + 2);
	map[0][M + 2] = 0;
	map[N + 1] = new char[M + 3];
	memset(map[N + 1], '#', M + 2);
	map[0][M + 2] = 0;

	mapSize = getIndex(N + 1, M + 1) + 1;
	Network net(mapSize * 2);
	int index;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			index = getIndex(i, j);
			if (map[i][j] == 'K') {
				S = index;
			}
			else if (map[i][j] == 'H') {
				T = index;
			}

			if (map[i][j] != '#') {
				if (map[i][j + 1] != '#') {
					net.addEdge(index + mapSize, index + 1);
					net.addEdge(index + 1 + mapSize, index);
				}
				if (map[i + 1][j] != '#') {
					net.addEdge(index + mapSize, index + (M + 2));
					net.addEdge(index + (M + 2) + mapSize, index);
				}
			}
		}
	}
	for (int i = 0; i < mapSize; i++) {
		if (i != S) {
			net.addEdge(i, mapSize + i);
		}
		else {
			net.addEdge(i, mapSize + i, 4);
		}
	}
	if (S + 1 == T || S + M + 2 == T || S - 1 == T || S - M - 2 == T) {
		printf("-1");
	}
	else {
		int flow = net.flow(S, T);
		int maxflow = 0;
		while (flow) {
			maxflow += flow;
			flow = net.flow(S, T);
		}
		printf("%d", maxflow);
	}
	return 0;
}