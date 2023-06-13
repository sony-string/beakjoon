#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <assert.h>
using namespace std;


typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;


struct Graph {
	vii* adjList;
	vi* parents;
	vii* minmaxToParent;
	int* level;
	Graph() {
		adjList = NULL;
		level = NULL;
		parents = NULL;
		minmaxToParent = NULL;
	}
};

Graph g;
vi route;


void dfs(int cur, int distFromBefo) {
	if (g.level[cur] == 0) {
		g.level[cur] = route.size() + 1;
	}
	int i, size;
	size = route.size();
	for (i = 0; size - (1 << i) >= 0; i++) {
		g.parents[cur].push_back(route[size - (1 << i)]);
	}
	if (g.level[cur] != 1) {
		g.minmaxToParent[cur].push_back(make_pair(distFromBefo, distFromBefo));
	}

	for (ii next : g.adjList[cur]) {
		if (g.level[next.first] != 0) {
			continue;
		}
		route.push_back(cur);
		dfs(next.first, next.second);
		route.pop_back();
	}
}


void makeMinMaxDP(int N) {
	bool loopFlag = true;
	size_t j = 1;
	ii minmaxPair;
	while (loopFlag) {
		loopFlag = false;
		for (int i = 1; i <= N; i++) {
			if (g.parents[i].size() > j) {
				minmaxPair.first = g.minmaxToParent[i][j - 1].first < g.minmaxToParent[g.parents[i][j - 1]][j - 1].first ?
					g.minmaxToParent[i][j - 1].first : g.minmaxToParent[g.parents[i][j - 1]][j - 1].first;
				minmaxPair.second = g.minmaxToParent[i][j - 1].second > g.minmaxToParent[g.parents[i][j - 1]][j - 1].second ?
					g.minmaxToParent[i][j - 1].second : g.minmaxToParent[g.parents[i][j - 1]][j - 1].second;

				g.minmaxToParent[i].push_back(minmaxPair);

				loopFlag = true;
			}
		}
		j++;
	}
}


int main() {
	int s, e, d;
	int N, K;
	ii lminmax;
	ii rminmax;
	scanf("%d", &N);

	g.adjList = new vii[N + 1];
	g.level = new int[N + 1];
	memset(g.level, 0, sizeof(int) * (N + 1));
	g.parents = new vi[N + 1];
	g.minmaxToParent = new vii[N + 1];

	for (int i = 0; i < N - 1; i++) {
		scanf("%d %d %d", &s, &e, &d);
		g.adjList[s].push_back(make_pair(e, d));
		g.adjList[e].push_back(make_pair(s, d));
	}

	dfs(1, 0);
	makeMinMaxDP(N);

	scanf("%d", &K);
	for (int i = 0; i < K; i++) {
		scanf("%d %d", &s, &e);

		lminmax.first = 10000000;
		lminmax.second = -1;
		rminmax.first = 10000000;
		rminmax.second = -1;

		if (g.level[s] < g.level[e]) {
			int temp = s;
			s = e;
			e = temp;
		}

		if (g.level[s] > g.level[e]) {
			for (int j = g.parents[s].size() - 1; g.level[s] != g.level[e]; j--) {
				if (g.level[s] - (1 << j) >= g.level[e]) {
					lminmax.first = lminmax.first < g.minmaxToParent[s][j].first ?
						lminmax.first : g.minmaxToParent[s][j].first;
					lminmax.second = lminmax.second > g.minmaxToParent[s][j].second ?
						lminmax.second : g.minmaxToParent[s][j].second;
					s = g.parents[s][j];
				}
			}
		}

		for (int j = g.parents[s].size() - 1; j >= 0; j--) {
			if (g.parents[s].size() <= j) {
				continue;
			}
			if (g.parents[s][j] != g.parents[e][j]) {
				lminmax.first = lminmax.first < g.minmaxToParent[s][j].first ?
					lminmax.first : g.minmaxToParent[s][j].first;
				lminmax.second = lminmax.second > g.minmaxToParent[s][j].second ?
					lminmax.second : g.minmaxToParent[s][j].second;
				s = g.parents[s][j];

				rminmax.first = rminmax.first < g.minmaxToParent[e][j].first ?
					rminmax.first : g.minmaxToParent[e][j].first;
				rminmax.second = rminmax.second > g.minmaxToParent[e][j].second ?
					rminmax.second : g.minmaxToParent[e][j].second;
				e = g.parents[e][j];
			}
		}

		if (s != e) {
			lminmax.first = lminmax.first < g.minmaxToParent[s][0].first ?
				lminmax.first : g.minmaxToParent[s][0].first;
			lminmax.second = lminmax.second > g.minmaxToParent[s][0].second ?
				lminmax.second : g.minmaxToParent[s][0].second;
			s = g.parents[s][0];

			rminmax.first = rminmax.first < g.minmaxToParent[e][0].first ?
				rminmax.first : g.minmaxToParent[e][0].first;
			rminmax.second = rminmax.second > g.minmaxToParent[e][0].second ?
				rminmax.second : g.minmaxToParent[e][0].second;
			e = g.parents[e][0];
		}
		assert(s == e);

		printf("%d %d\n", (lminmax.first < rminmax.first ? lminmax.first : rminmax.first),
			(lminmax.second > rminmax.second ? lminmax.second : rminmax.second));
	}

	return 0;
}