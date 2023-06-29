#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;


typedef vector<int> vi;


int main() {
	int memberCount = 0;
	int* scoreList;
	int s, e, best = 1e9;
	int** graph;

	scanf("%d", &memberCount);
	scoreList = new int[memberCount + 1];
	graph = new int* [memberCount + 1];
	for (int i = 0; i < memberCount + 1; i++) {
		graph[i] = new int[memberCount + 1];
		memset(graph[i], 0, sizeof(int) * (memberCount + 1));
	}

	scanf("%d %d", &s, &e);
	while (s != -1) {
		graph[s][e] = 1;
		graph[e][s] = 1;
		scanf("%d %d", &s, &e);
	}

	for (int m = 1; m < memberCount + 1; m++) {
		for (s = 1; s <= memberCount; s++) {
			if (graph[s][m] == 0) {
				continue;
			}
			for (e = 1; e <= memberCount; e++) {
				if (graph[m][e] == 0 || s == e) {
					continue;
				}
				if (graph[s][e] == 0) {
					graph[s][e] = graph[s][m] + graph[m][e];
				}
				else {
					graph[s][e] = min(graph[s][e], graph[s][m] + graph[m][e]);
				}
			}
		}
	}

	for (int i = 1; i < memberCount + 1; i++) {
		best = 0;
		for (int k = 1; k < memberCount + 1; k++) {
			best = max(best, graph[i][k]);
		}
		scoreList[i] = best;
	}

	best = 1e9;
	for (int i = 1; i <= memberCount; i++) {
		best = min(scoreList[i], best);
	}

	assert(best > 0);
	
	vi reservedLeader;
	for (int i = 1; i < memberCount + 1; i++) {
		if (scoreList[i] == best) {
			reservedLeader.push_back(i);
		}
	}

	printf("%d %d\n", best, reservedLeader.size());
	for (auto i : reservedLeader) {
		printf("%d ", i);
	}
	return 0;
}