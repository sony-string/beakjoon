#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <vector>
#include <string.h>
#include <math.h>
#include <assert.h>
using namespace std;


struct Node {
	int idx;
	Node* nextNode;
	Node* lastNode;
	Node() {
		idx = 0;
		nextNode = NULL;
		lastNode = this;
	}
};


typedef int V;

int dfn = 0;
vector<int> eulertour;
vector<int> _E;
int** spT;
int* H;

void dfs(V* table, Node* adjList, int idx) {
	table[idx] = dfn;
	H[idx] = eulertour.size();
	eulertour.push_back(dfn);
	_E.push_back(idx);
	dfn++;

	Node* e = adjList[idx].nextNode;
	while (e != NULL) {
		if (table[e->idx] == -1) {
			dfs(table, adjList, e->idx);
			eulertour.push_back(table[idx]);
		}
		e = e->nextNode;
	}
}

void make_sparseTable(int** spT, int logsize, int eulersize) {
	int i, j;
	int r;
	for (j = 0; j < eulersize; j++) {
		spT[0][j] = eulertour[j];
	}
	for (i = 1; i <= logsize; i++) {
		for (j = 0; j <= eulersize - (1 << i); j++) {
			r = j + (1 << i);
			spT[i][j] = spT[i - 1][j] < spT[i - 1][r - (1 << (i - 1))] ? spT[i - 1][j] : spT[i - 1][r - (1 << (i - 1))];
		}
	}
}

int main() {
	V* vertice;
	Node* adjList, * edge;
	int numVertice;
	int s, e, temp;
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
		vertice[i] = -1;
	}

	for (int i = 0; i < numVertice - 1; i++) {
		scanf("%d %d", &s, &e);
		edge = new Node;
		edge->idx = e;
		adjList[s].lastNode->nextNode = edge;
		adjList[s].lastNode = edge;

		edge = new Node;
		edge->idx = s;
		adjList[e].lastNode->nextNode = edge;
		adjList[e].lastNode = edge;
	}

	dfs(vertice, adjList, 1);
	make_sparseTable(spT, logsize, 2 * numVertice - 1);
	scanf("%d", &numq);

	edge = adjList[1].nextNode;

	for (int i = 0; i < numq; i++) {
		scanf("%d %d", &s, &e);
		sdfn = vertice[s];
		edfn = vertice[e];
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
		printf("%d\n", _E[lca]);
	}

	return 0;
}