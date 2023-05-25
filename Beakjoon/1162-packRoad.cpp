#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

typedef long long li;
typedef pair<li, pair<int, int>> E;
#define fore(a, b) for(int i = a; i < b; i++)
#ifndef LMAX
#define LMAX 9223372036854775807
#endif


typedef struct Node {
	int index;
	int value;
	struct Node* nextNode;
	struct Node* lastNode;
} Node;



int main() {
	priority_queue<E, vector<E>, greater<E>> heaps;
	Node* cities, * edge;
	E q;

	int numCities, numRoads, numPack;
	int src, dst, cost;
	li** dist;
	scanf("%d %d %d", &numCities, &numRoads, &numPack);

	cities = (Node*)calloc(numCities + 1, sizeof(Node));
	int** visited = (int**)calloc(numCities + 1, sizeof(int*));

	fore(0, numCities + 1) {
		cities[i].index = i;
		cities[i].lastNode = &cities[i];
		visited[i] = (int*)calloc(numPack + 1, sizeof(int));
	}

	fore(0, numRoads) {
		scanf("%d %d %d", &src, &dst, &cost);
		edge = (Node*)calloc(1, sizeof(Node));
		edge->index = dst;
		edge->value = cost;
		cities[src].lastNode->nextNode = edge;
		cities[src].lastNode = edge;

		edge = (Node*)calloc(1, sizeof(Node));
		edge->index = src;
		edge->value = cost;
		cities[dst].lastNode->nextNode = edge;
		cities[dst].lastNode = edge;
	}

	dist = (li**)calloc(numPack + 1, sizeof(li*));
	fore(0, numPack + 1) {
		dist[i] = (li*)calloc(numCities + 1, sizeof(li));
		for (int j = 0; j < numCities + 1; j++) {
			dist[i][j] = -1;
		}
		dist[i][1] = 0;
	}

	q.first = 0;
	q.second.first = 1;
	q.second.second = numPack;
	heaps.push(q);
	int k;

	while (!heaps.empty()) {
		q = heaps.top();
		heaps.pop();
		k = q.second.second;
		src = q.second.first;
		edge = &cities[src];
		if (src == numCities || visited[src][k] == 1) {
			continue;
		}
		visited[src][k] = 1;
		edge = edge->nextNode;
		while (edge != NULL) {
			dst = edge->index;
			cost = edge->value;
			if (dist[k][dst] > dist[k][src] + cost) {
				dist[k][dst] = dist[k][src] + cost;
				q.first = dist[k][dst];
				q.second.first = dst;
				q.second.second = k;
				heaps.push(q);
			}
			else if (dist[k][dst] == -1) {
				dist[k][dst] = dist[k][src] + cost;
				q.first = dist[k][dst];
				q.second.first = dst;
				q.second.second = k;
				heaps.push(q);
			}

			if (k > 0) {
				if (dist[k - 1][dst] > dist[k][src]) {
					dist[k - 1][dst] = dist[k][src];
					q.first = dist[k - 1][dst];
					q.second.first = dst;
					q.second.second = k - 1;
					heaps.push(q);
				}
				else if (dist[k - 1][dst] == -1) {
					dist[k - 1][dst] = dist[k][src];
					q.first = dist[k - 1][dst];
					q.second.first = dst;
					q.second.second = k - 1;
					heaps.push(q);
				}
			} 
			edge = edge->nextNode;
		}
	}


	li result = LMAX;
	fore(0, numPack + 1) {
		if (dist[i][numCities] < result && dist[i][numCities] != -1) {
			result = dist[i][numCities];
		}
	}

	printf("%lld", result);
	return 0;
}