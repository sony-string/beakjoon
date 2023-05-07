#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int** dist;
	int* area;
	int capacity, numRoad, numArea;
	int sum, best;
	int src, dst;

	scanf("%d %d %d", &numArea, &capacity, &numRoad);
	area = (int*)malloc(numArea * sizeof(int));
	dist = (int**)malloc(numArea * sizeof(int*));
	for (int i = 0; i < numArea; i++) {
		scanf("%d", area + i);
		dist[i] = (int*)malloc(numArea * sizeof(int));
		memset(dist[i], -1, numArea * sizeof(int));
		dist[i][i] = 0;
	}

	for (int i = 0; i < numRoad; i++) {
		scanf("%d %d", &src, &dst);
		src--; dst--;
		scanf("%d", &dist[src][dst]);
		dist[dst][src] = dist[src][dst];
	}

	for (int u = 0; u < numArea; u++) {
		for (int s = 0; s < numArea; s++) {
			if (dist[s][u] == -1) {
				continue;
			}
			for (int e = 0; e < numArea; e++) {
				if (dist[u][e] == -1) {
					continue;
				}
				if (dist[s][e] == -1) {
					dist[s][e] = dist[s][u] + dist[u][e];
				}
				else if (dist[s][u] + dist[u][e] < dist[s][e]) {
					dist[s][e] = dist[s][u] + dist[u][e];
				}
			}
		}
	}

	best = 0;

	for (int s = 0; s < numArea; s++) {
		sum = 0;
		for (int e = 0; e < numArea; e++) {
			if (dist[s][e] == -1) {
				continue;
			}
			else if (dist[s][e] <= capacity) {
				sum += area[e];
			}
		}
		if (best < sum) {
			best = sum;
		}
	}

	printf("%d", best);
	return 0;
}