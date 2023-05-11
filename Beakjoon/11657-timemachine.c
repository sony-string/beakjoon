#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	long long key;
	long long value;
	struct Node* nextNode;
	struct Node* lastNode;
} Node;

int main() {
	const long long INF = 2139062143;

	long long numCities, numBuses;
	long long src, dst, cost;
	long long infFlag = 0;
	long long* dists;
	Node* adjList, * node;

	scanf("%lld %lld", &numCities, &numBuses);
	dists = (long long*)malloc(numCities * sizeof(long long));
	adjList = (Node*)malloc(numCities * sizeof(Node));
	for (long long i = 0; i < numCities; i++) {
		adjList[i].key = i;
		adjList[i].value = 0;
		adjList[i].nextNode = NULL;
		adjList[i].lastNode = &adjList[i];
		dists[i] = INF;
	}
	dists[0] = 0;

	for (long long i = 0; i < numBuses; i++) {
		scanf("%lld %lld %lld", &src, &dst, &cost);
		src--; dst--;
		node = (Node*)calloc(1, sizeof(Node));
		node->value = cost;
		node->key = dst;
		adjList[src].lastNode->nextNode = node;
		adjList[src].lastNode = node;
	}

	for (long long t = 0; t < numCities; t++) {
		for (long long m = 0; m < numCities; m++) {
			if (dists[m] == INF) {
				continue;
			}
			node = adjList[m].nextNode;
			while (node != NULL) {
				dst = node->key;
				if (dists[dst] == INF) {
					dists[dst] = dists[m] + node->value;
				}
				else if (dists[dst] > dists[m] + node->value) {
					dists[dst] = dists[m] + node->value;
				}
				node = node->nextNode;
			}
		}
		if (dists[0] < 0) {
			infFlag = 1;
			break;
		}
	}

	for (long long m = 0; m < numCities; m++) {
		if (infFlag == 1) {
			break;
		}
		if (dists[m] == INF) {
			continue;
		}
		node = adjList[m].nextNode;
		while (node != NULL) {
			dst = node->key;
			if (dists[dst] > dists[m] + node->value) {
				infFlag = 1;
				break;
			}
			node = node->nextNode;
		}
	}
	
	if (infFlag == 1) {
		printf("-1");
		return 0;
	}
	else {
		for (long long i = 1; i < numCities; i++) {
			if (dists[i] == INF) {
				printf("-1");
			}
			else { 
				printf("%lld", dists[i]);
			}
			if (i != numCities - 1) {
				printf("\n");
			}
		}
	}
	return 0;
}