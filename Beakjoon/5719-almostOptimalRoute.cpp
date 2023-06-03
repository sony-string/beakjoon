#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <vector>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<pair<int, int>> vii;


struct Graph {
	vii* adjList;
	int numV;
	Graph(int n) {
		adjList = new vii[n];
		numV = n;
	}
	~Graph() {
		delete[](adjList);
	}
};

#define MAX 1000000000

int V, E;
vi dist;
vi* discardEdge;
vi* parent;

priority_queue<ii, vector<ii>, greater<ii>> pq;


void deleteEdges(int cur, int s) {
	for (int i = 0; i < parent[cur].size(); i++) {
		if (discardEdge[parent[cur][i]][cur] == 1) {
			continue;
		}
		discardEdge[parent[cur][i]][cur] = 1;
		if (parent[cur][i] != s) {
			deleteEdges(parent[cur][i], s);
		}
	}
}


void getroute(int s, int e, Graph* g, int pass) {
	int cur;

	dist[s] = 0;
	pq.push(make_pair(dist[s], s));
	while (!pq.empty()) {
		cur = pq.top().second;
		if (cur == e) {
			break;
		}
		if (dist[cur] < pq.top().first) {
			pq.pop();
			continue;
		}
		pq.pop();

		for (const auto& i : g->adjList[cur]) {
			if (discardEdge[cur][i.first] == 1) {
				continue;
			}
			if (dist[i.first] > dist[cur] + i.second) {
				dist[i.first] = dist[cur] + i.second;
				pq.push(make_pair(dist[i.first], i.first));
				if (pass == 0) {
					parent[i.first].clear();
					parent[i.first].push_back(cur);
				}
			}
			else if (dist[i.first] == dist[cur] + i.second && pass == 0) {
				parent[i.first].push_back(cur);
			}
		}
	}
	if (pass == 0) {
		deleteEdges(e, s);
	}
}



int main() {
	Graph* g;
	int s, e, d;
	int start, end;

	scanf("%d %d", &V, &E);
	while (V != 0 || E != 0) {
		scanf("%d %d", &start, &end);
		dist.assign(V, MAX);
		discardEdge = new vi[V];
		parent = new vi[V];
		pq = priority_queue<ii, vector<ii>, greater<ii>>();
		for (int i = 0; i < V; i++) {
			discardEdge[i].assign(V, 0);
		}
		g = new Graph(V);
		for (int i = 0; i < E; i++) {
			scanf("%d %d %d", &s, &e, &d);
			g->adjList[s].push_back(make_pair(e, d));
		}

		getroute(start, end, g, 0);
		if (dist[end] == MAX) {
			printf("-1\n");
			delete(g);
			delete[](discardEdge);
			delete[](parent);
			scanf("%d %d", &V, &E);
			continue;
		}
		dist.assign(V, MAX);
		pq = priority_queue<ii, vector<ii>, greater<ii>>();
		getroute(start, end, g, 1);

		if (dist[end] == MAX) {
			printf("-1\n");
		}
		else {
			printf("%d\n", dist[end]);
		}
		delete(g);
		delete[](discardEdge);
		delete[](parent);

		scanf("%d %d", &V, &E);
	}

	return 0;
}