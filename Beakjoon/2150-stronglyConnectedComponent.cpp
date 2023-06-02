#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <vector>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <algorithm>
using namespace std;

#ifndef MIN
#define MIN(a, b) (a < b ? a : b)
#endif

struct Graph {
	int numVertex;
	vector<int>* adjList;
	void makeGraph(int n) {
		numVertex = n;
		adjList = new vector<int>[n + 1];
	}
};

Graph graph;
int sccCount = 0;
int V, E;
vector<int> subG[10001];
bool visited[10001];
vector<int> dfslow, dfn;
vector<int> sccnumber;
int dfncount = 0;


void dfs(int idx, vector<int>& stack) {
	stack.push_back(idx);
	visited[idx] = true;
	dfn[idx] = dfncount;
	dfslow[idx] = dfncount;
	dfncount++;
	
	for (vector<int>::iterator i = graph.adjList[idx].begin(); i != graph.adjList[idx].end(); i++) {
		if (dfn[*i] == -1) {
			dfs(*i, stack);
		}
		if (visited[*i]) {
			dfslow[idx] = MIN(dfslow[idx], dfslow[*i]);
		}
	}

	if (dfslow[idx] == dfn[idx]) {
		int v;
		sccCount++;
		while (1) {
			v = stack.back();
			stack.pop_back();
			visited[v] = false;
			subG[sccCount].push_back(v);
			sccnumber[v] = sccCount;
			if (v == idx) {
				break;
			}
		}
	}
}


int main() {
	vector<int> stack;
	scanf("%d %d", &V, &E);
	graph.makeGraph(V);
	memset(visited, false, sizeof(bool) * (V + 1));
	dfslow.assign(V + 1, 0);
	dfn.assign(V + 1, -1);
	sccnumber.assign(V + 1, -1);

	int s, e;
	for (int i = 0; i < E; i++) {
		scanf("%d %d", &s, &e);
		graph.adjList[s].push_back(e);
	}

	for (int i = 1; i <= V; i++) {
		if (dfn[i] == -1) {
			dfs(i, stack);
		}
	}

	printf("%d\n", sccCount);
	for (int i = 1; i <= V; i++) {
		if (!visited[i]) {
			sort(subG[sccnumber[i]].begin(), subG[sccnumber[i]].end());
			for (vector<int>::iterator iter = subG[sccnumber[i]].begin(); iter != subG[sccnumber[i]].end(); iter++) {
				visited[*iter] = true;
				printf("%d ", *iter);
			}
			printf("-1\n");
		}
	}

	return 0;
}