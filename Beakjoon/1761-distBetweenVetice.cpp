#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <vector>
#include <string.h>
#include <math.h>
using namespace std;


struct Node {
	int idx;
	int value;
	Node* nextNode;
	Node* lastNode;
	Node() {
		idx = 0;
		nextNode = NULL;
		lastNode = this;
		value = 0;
	}
};


typedef pair<int, int> V;

int dfn = 0;
vector<int> eulertour;
vector<int> _E;
int** spT;
int* H;

void dfs(V* table, Node* adjList, int idx, int sum) {
	table[idx].first = dfn;
	table[idx].second = sum;
	H[idx] = eulertour.size();
	eulertour.push_back(dfn);
	_E.push_back(idx);
	dfn++;

	Node* e = adjList[idx].nextNode;
	while (e != NULL) {
		if (table[e->idx].first == -1) {
			dfs(table, adjList, e->idx, sum + e->value);
			eulertour.push_back(table[idx].first);
		}
		e = e->nextNode;
	}
}

void make_sparseTable(int** spT, int logsize, int eulersize) {
	int i, j;
	int l, r;
	for (j = 0; j < eulersize; j++) {
		spT[0][j] = eulertour[j];
	}
	for (i = 1; i <= logsize; i++) {
		for (j = 0; j <= eulersize - (1 << i); j++) {
			l = j;
			r = j + (1 << i);
			spT[i][j] = spT[i - 1][j] < spT[i - 1][r - (1 << (i - 1))] ? spT[i - 1][j] : spT[i - 1][r - (1 << (i - 1))];
		}
	}
}

int main() {
	V* vertice;
	Node* adjList, * edge;
	int numVertice;
	int s, e, dist, temp;
	int numq;

	int sdfn, edfn;
	int lca;
	int logsize;

	scanf("%d", &numVertice);
	logsize = (int)log2(2 * numVertice - 1);
	vertice = new V[numVertice + 1];
	H = new int[numVertice + 1];
	adjList = new Node[numVertice + 1];
	spT = new int* [logsize + 1];

	for (int i = 0; i <= logsize; i++) {
		spT[i] = new int[2 * numVertice - 1];
	}
	for (int i = 1; i <= numVertice; i++) {
		vertice[i].first = -1;
	}
	vertice[1].second = 0;

	for (int i = 0; i < numVertice - 1; i++) {
		scanf("%d %d %d", &s, &e, &dist);
		edge = new Node;
		edge->idx = e;
		edge->value = dist;
		adjList[s].lastNode->nextNode = edge;
		adjList[s].lastNode = edge;

		edge = new Node;
		edge->idx = s;
		edge->value = dist;
		adjList[e].lastNode->nextNode = edge;
		adjList[e].lastNode = edge;
	}

	dfs(vertice, adjList, 1, 0);
	make_sparseTable(spT, logsize, 2 * numVertice - 1);
	scanf("%d", &numq);

	edge = adjList[1].nextNode;

	for (int i = 0; i < numq; i++) {
		scanf("%d %d", &s, &e);
		if (s == e) {
			printf("0\n");
			continue;
		}
		sdfn = vertice[s].first;
		edfn = vertice[e].first;
		if (sdfn > edfn) {
			temp = sdfn;
			sdfn = edfn;
			edfn = temp;

			temp = s;
			s = e;
			e = temp;
		}
		logsize = (int)log2((H[e] - H[s] + 1));
		lca = spT[logsize][H[s]] < spT[logsize][H[e] - (1 << logsize) + 1] ?
			spT[logsize][H[s]] : spT[logsize][H[e] - (1 << logsize) + 1];
		printf("%d\n", vertice[s].second + vertice[e].second - 2 * vertice[_E[lca]].second);
	}

	return 0;
}