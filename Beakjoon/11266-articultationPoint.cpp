#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <functional>
#include <algorithm>
#include <math.h>
#include <stack>
using namespace std;


#ifndef MIN
#define MIN(a ,b) ((a) < (b) ? (a) : (b))
#endif

#define fore(a, b, c) for (int i = a; i < b; i += c)

typedef pair<int, int> LowTable;


int total = 0;


struct Node {
	int degree;
	int* edges;
};


void findArticulationPoint(int* isArticul, Node* adjList, LowTable* lt, int s, stack<pair<int, int>> st) {
	int sDegree = 0;
	st.push(make_pair(s, 0));
	lt[s].first = 0;
	lt[s].second = 0;
	int* edges;
	int e, cur;
	int idx;
	int low = -1;
	int count = 1;

	while (!st.empty()) {
		cur = st.top().first;
		idx = st.top().second;
		if (lt[cur].first <= low && isArticul[cur] == 0) {
			isArticul[cur] = 1;
			total++;
		}
		lt[cur].second = MIN(lt[cur].second, low);

		st.pop();
		edges = adjList[cur].edges;

		while (idx < adjList[cur].degree) {
			e = adjList[cur].edges[idx];
			if (lt[e].first == -1) {
				lt[e].first = count;
				lt[e].second = lt[cur].first;
				count++;
				if (s == cur) {
					sDegree++;
				}
				st.push(make_pair(cur, idx + 1));
				cur = e;
				idx = 0;
				continue;
			}
			else {
				lt[cur].second = MIN(lt[e].first, lt[cur].second);
			}
			idx++;
		}
		low = lt[cur].second;
	}

	if (sDegree < 2 && isArticul[s] == 1) {
		isArticul[s] = 0;
		total--;
	}
}



int main() {
	stack<pair<int, int>> st;
	LowTable* lt;
	vector<int>* adj;
	Node* adjList;
	int* aP;

	int numNodes, numEdges;
	int s, e;
	scanf("%d %d", &numNodes, &numEdges);
	
	lt = new LowTable[numNodes + 1];
	adj = new vector<int>[numNodes + 1];
	adjList = new Node[numNodes + 1];
	aP = new int[numNodes + 1];
	memset(aP, 0, (numNodes + 1) * sizeof(int));


	fore(0, numEdges, 1) {
		scanf("%d %d", &s, &e);
		adj[s].push_back(e);
		adj[e].push_back(s);
	}

	fore(1, numNodes + 1, 1) {
		lt[i].first = -1;
		adjList[i].degree = adj[i].size();
		adjList[i].edges = adj[i].data();
	}

	fore(1, numNodes + 1, 1) {
		if (lt[i].first == -1) {
			findArticulationPoint(aP, adjList, lt, i, st);
		}

		
	}

	printf("%d\n", total);
	fore(1, numNodes + 1, 1) {
		if (aP[i] == 1) {
			printf("%d ", i);
		}
	}

	return 0;
}